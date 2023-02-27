---
title: ES 删除字段
date: 2020-01-19
categories: ElasticSearch
tags: [ElasticSearch,ES]
---


# es删除字段

[![img](https://upload.jianshu.io/users/upload_avatars/20803889/06ccb157-7e9e-4f36-8f59-65f37832772d.jpg?imageMogr2/auto-orient/strip|imageView2/1/w/96/h/96/format/webp)](https://www.jianshu.com/u/6d5b80cdfe5d)

[修行者12138](https://www.jianshu.com/u/6d5b80cdfe5d)关注

2020.12.14 20:53:55字数 432阅读 8,123

原索引mappings如下，有full_name和short_name两个字段



```json
{
    "audit_demo": {
        "mappings": {
            "_doc": {
                "properties": {
                    "full_name": {
                        "type": "text",
                        "analyzer": "ik_max_word"
                    },
                    "short_name": {
                        "type": "keyword"
                    }
                }
            }
        }
    }
}
```

想要删掉short_name字段，修改后mappings如下



```json
{
    "audit_demo_bak": {
        "mappings": {
            "_doc": {
                "properties": {
                    "full_name": {
                        "type": "text",
                        "analyzer": "ik_max_word"
                    }
                }
            }
        }
    }
}
```



#### 步骤1 删除原索引中待删除字段的数据

注意
1.只是删除数据，不是删除字段
2.如果不删除字段数据，后面reindex时依然会把待删除字段的值带到新索引，即使设置新索引的dynamic为false



```bash
POST {{di}}/audit_demo/_update_by_query
{
    "script": {
        "lang": "painless",
        "inline": "ctx._source.remove(\"short_name\")"
    },
    "query": {
        "match_all": {}
    }
}
```

#### 步骤2 新建一个索引，索引结构在原索引上删除short_name字段



```bash
PUT {{di}}/audit_demo_bak
{
    "settings": {
        "number_of_shards": "2",
        "number_of_replicas": "2",
        "max_result_window": 100000,
        "analysis": {
            "analyzer": {
                "ik": {
                    "tokenizer": "ik_max_word"
                }
            }
        }
    },
    "mappings": {
        "_doc": {
            "properties": {
                "full_name": {
                    "type": "text",
                    "analyzer": "ik_max_word"
                }
            }
        }
    }
}
```

#### 步骤3 同步数据



```bash
POST {{di}}/_reindex
{
    "source": {
        "index": "audit_demo"
    },
    "dest": {
        "index": "audit_demo_bak"
    }
}
```

#### 步骤4 删除原索引



```undefined
DELETE {{di}}/audit_demo
```

#### 步骤5 新建一个名为原索引名的索引，reindex同步数据，然后删除步骤2新建的索引



#### 注意事项

步骤4和步骤5，这两个步骤，耗时较长，在这段时间，索引是不可用的，一般在业务低峰期执行操作没啥问题。如果想要减少索引不可用的时间，有以下两个方案

方案1
删除原索引后，为新索引设置别名为原索引
备注：原索引未删除时，为新索引设置别名为原索引会报错



```undefined
PUT {{di}}/audit_demo_bak/_alias/audit_demo
```

方案2
步骤1开始之前，就为原索引设置别名，应用程序通过别名访问索引，步骤4开始之前，删除原索引与别名的关系，新增新索引与别名的关系，应用程序通过别名可以访问到新索引。
虽然这两个步骤的耗时极小，但是还是有可能在这段期间有数据更改，所以还是尽量在业务低峰期操作。