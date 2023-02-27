---
title: ES 基础
date: 2022-07-09 23:13:00
categories: ElasticSearch
tags: [ElasticSearch,ES]
---

# ES简介 


ES简介
// ES是一个基于RESTful web接口并且构建在Apache Lucene之上的开源分布式搜索引擎。
ES的倒排索引
// 通俗的讲: 倒排索引，是通过分词策略，形成了词和文章的映射关系表，这种词典+映射表即为倒排索引。有了倒排索引，就能实现 o（1）时间复杂度的效率检索文章了，极大的提高了检索效率。
// 专业的讲: 倒排索引，从词出发，记载了这个词在哪些文档中出现过，由两部分组成——词典和倒排表;倒排索引的底层实现是基于：FST（Finite State Transducer）数据结构;FST 有两个优点:
// (1) 空间占用小。通过对词典中单词前缀和后缀的重复利用，压缩了存储空间;
// (2) 查询速度快。O(len(str))的查询时间复杂度;



# ES基础概念   

// 从大到小一次介绍：
集群: cluster : ES本质上是一个分布式数据库，允许多台服务器协同工作，每台服务器可以运行1个或者多个Elastic实例，完整的分布式服务称为集群；
节点: node : 组成集群的一个个实例，其中一个实例称为一个节点；
分片: shard : 一个数据非常大，需要对数据分块存储，这里的一块数据称为一个shard (在创建索引的时候，就需要指定分块的数量和副本个数);
副本: replica : 数据分块后，需要进行备灾，一个块损坏后，需要有其他副本顶上，这里的副本其实也是一个shard;
索引: index : 类似关系型数据库中的数据库，目前我们说的一个个检索引擎，实际上就是一个个的index;
类型: type : 类似关系型数据库中的数据表，跟数据库不同的是，一个index现在只允许创建一个type, 以后的版本中就没有type的概念了;
文档: document : 存入索引中的一条具体的数据，由多个字段组成;
字段: field : 文档中的一个属性;
词项: term : 搜索时的一个单位，代表了文本中的一个词;
词元: token : 词项在字段文本中的一次出现，包括词项的文本、开始、结束的偏移以及词条类型;


// DSL: Domain Specified Language:特定领域的语言  下面看到的拼的ES数据包的结构称为DSL,可以写到超级复杂


// 参考: http://www.ruanyifeng.com/blog/2017/08/elasticsearch.html


ES基础信息查询:

```js
ES基础信息查询    
// 看下都支持哪些基础查询操作

curl -u user:111 -X GET '1.1.1.1:8200/_cat'


// 返回结果：
/_cat/allocation
/_cat/shards
/_cat/shards/{index}
/_cat/master
/_cat/nodes
/_cat/tasks
/_cat/indices
/_cat/indices/{index}
/_cat/segments
/_cat/segments/{index}
/_cat/count
/_cat/count/{index}
/_cat/recovery
/_cat/recovery/{index}
/_cat/health
/_cat/pending_tasks
/_cat/aliases
/_cat/aliases/{alias}
/_cat/thread_pool
/_cat/thread_pool/{thread_pools}
/_cat/plugins
/_cat/fielddata
/_cat/fielddata/{fields}
/_cat/nodeattrs
/_cat/repositories
/_cat/snapshots/{repository}
/_cat/templates


// 比如查询ES集群下所有的索引index信息，可使用下面的查询方式
curl -u user:111 -X GET '1.1.1.1:8200/_cat/indices?v'

返回：
// health status index            uuid                   pri rep docs.count docs.deleted store.size pri.store.size
// yellow open   abcd_efg     MFHsrc_MT26YE6_T-o15eQ   6   1          0            0      1.5kb          1.5kb
// yellow open   zhengxin_online  o0_G3sIIQwienlB1ssK5QA   6   1    1407738         9685    501.3mb        501.3mb


// health为yellow的原因是：这个ES集群只有一个node,也就是说缺少备灾能力，所以健康状态是yellow, yellow表示不影响使用，但是有风险
```



创建索引: 设置分片数和副本数    

```js
创建索引: 设置分片数和副本数     
// 6个主分片，1个副本，也就是说，会创建12个分片出来，同一份数据分别位于一个主分片和一个副分片，且不位于同一个节点(假设是ES集群，且有不止一个节点，主要是备灾和并行查询)
// 关于分片数量设置: ES的同学告知的结论是：一个分片大小控制在10G~30G，当分片数据过大后，就需要重新设置分片数，然后通过reindex实现；
// 索引名称: abcd_efg (索引名必须小写: test: "Invalid index name [abcd_efg], must be lowercase")


curl -u user:111 -X PUT '1.1.1.1:8200/abcd_efg?pretty' -H 'Content-Type: application/json' -d '
{
    "settings": {
        "number_of_shards": 6,
        "number_of_replicas": 1
    }
}'


// 返回结果：
{
  "acknowledged" : true,
  "shards_acknowledged" : true,
  "index" : "abcd_efg"
}
```



创建索引结构、查询索引结构

```js
创建索引结构     

// 创建一张表，叫entinfo，其中有4个字段组成，分别是bdCode、logo、entName、coreName
// "dynamic":"strict" 表示: 当我们向index写入数据的时候，如果多写了一个map中不存在的key,则报错，否则，ES会根据新字段value的类型自动在map中添加一个字段
curl -u user:111 -X PUT '1.1.1.1:8200/abcd_efg/entinfo/_mapping?pretty=true' -H 'Content-Type: application/json' -d '
{
    "entinfo":{
        "dynamic":"strict",
        "properties":{
            "bdCode":{
                "type":"keyword"
            },
            "logo":{
                "type":"keyword",
                "index":false
            },
            "entName" : {
                "type" : "text",
                "analyzer" : "ik_max_word"
            },
            "coreName" : {
                "type" : "keyword"
            }
        }
    }
}'

// 返回结果
{
  "acknowledged" : true
}


查询索引结构
curl -u user:111 -X GET '1.1.1.1:8200/abcd_efg/entinfo/_mapping?pretty=true'


// 返回结果
{
  "abcd_efg" : {
    "mappings" : {
      "entinfo" : {
        "dynamic" : "strict",
        "properties" : {
          "bdCode" : {
            "type" : "keyword"
          },
          "coreName" : {
            "type" : "keyword"
          },
          "entName" : {
            "type" : "text",
            "analyzer" : "ik_max_word"
          },
          "logo" : {
            "type" : "keyword",
            "index" : false
          }
        }
      }
    }
  }
}
```



添加索引数据、查看索引数据

```js
添加索引数据

// 可以指定doc的key, 也可以不指定，不指定的话，系统会生成一个全局唯一的key支持查询

curl -u user:111 -X PUT '1.1.1.1:8200/abcd_efg/entinfo/287832028393?pretty' -H 'Content-Type: application/json' -d '
{
    "bdCode": 287832028393,
    "entName": "北京网讯科技有限公司",
    "logo": "https://zhengxin-pub.bj.bcebos.com/logopic/6829dfa6c9b4714a6456796fd887c870_fullsize.jpg",
    "coreName": "robin"
}'

// 返回结果：
{
  "_index" : "abcd_efg",
  "_type" : "entinfo",
  "_id" : "287832028393",
  "_version" : 1,
  "result" : "created",
  "_shards" : {
    "total" : 2,
    "successful" : 1,
    "failed" : 0
  },
  "_seq_no" : 0,
  "_primary_term" : 1
}




查看指定key的索引数据
curl -u user:111 -X GET '1.1.1.1:8200/abcd_efg/entinfo/287832028393?pretty'
// 返回结果
{
  "_index" : "abcd_efg",
  "_type" : "entinfo",
  "_id" : "287832028393",
  "_version" : 1,
  "found" : true,
  "_source" : {
    "bdCode" : 287832028393,
    "entName" : "北京网讯科技有限公司",
    "logo" : "https://zhengxin-pub.bj.bcebos.com/logopic/6829dfa6c9b4714a6456796fd887c870_fullsize.jpg",
    "coreName" : "robin"
  }
}
```



基础数据查询 

```js
基础数据查询     
// ES的查询有多种方式，其中包括 match match_phrase multi_match term 以及 must、should、must_not
// 参考: https://www.cnblogs.com/yjf512/p/4897294.html

curl -u user:111  -X GET "1.1.1.1:8200/abcd_efg/entinfo/_search?pretty=true" -H 'Content-Type: application/json' -d '
{
  "from": 0,
  "size": 2,
  "query": {
    "match": {
      "entName": {
        "query": ""
      }
    }
  },
  "_source":[
    "entName","logo"
  ]
}'

// 返回结果
{
  "took" : 2,
  "timed_out" : false,
  "_shards" : {
    "total" : 6,
    "successful" : 6,
    "skipped" : 0,
    "failed" : 0
  },
  "hits" : {
    "total" : 1,
    "max_score" : 0.8630463,
    "hits" : [
      {
        "_index" : "abcd_efg",
        "_type" : "entinfo",
        "_id" : "287832028393",
        "_score" : 0.8630463,
        "_source" : {
          "entName" : "北京网讯科技有限公司",
          "logo" : "https://zhengxin-pub.bj.bcebos.com/logopic/6829dfa6c9b4714a6456796fd887c870_fullsize.jpg"
        }
      }
    ]
  }
}
// 其中took是检索的耗时，不包含网络的耗时，单位是毫秒,timed_out表示是否超时了;其他的应该都看得懂了;
```

# pretty

在任意的查询[字符串](https://so.csdn.net/so/search?q=字符串&spm=1001.2101.3001.7020)中增加`pretty`参数，会让[Elasticsearch](https://so.csdn.net/so/search?q=Elasticsearch&spm=1001.2101.3001.7020)**美化输出(pretty-print)**JSON响应以便更加容易阅读。

`_source`字段不会被美化，它的样子与我们输入的一致。

# dynamic

- 动态映射（dynamic：true）：动态添加新的字段（或缺省）。
- 静态映射（dynamic：false）：忽略新的字段。在原有的映射基础上，当有新的字段时，不会主动的添加新的映射关系，只作为查询结果出现在查询中。
- 严格模式（dynamic： strict）：如果遇到新的字段，就抛出异常。

# 操作

## 插入



