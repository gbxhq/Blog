## 基本搜索

```http
{
    "query": {
        "bool": {
            "must": [
                {
                    "match_all": {}
                }
            ]
        }
    },
    "from": 0,
    "size": 1
}
```
### Group BY
```
{
    "query": {
        "bool": {
            "must": [
                {
                    "match_all": {}
                }
            ]
        }
    },
    "from": 0,
    "size": 0,
    "aggregations": {
        "mid": {
            "aggregations": {
                "terminal": {
                    "terms": {
                        "field": "terminal",
                        "size": 0
                    }
                }
            },
            "terms": {
                "field": "mid",
                "size": "1"
            }
        }
    }
}
```

### Distinct Count
```
{
    "query": {
        "bool": {
            "must": [
                {
                    "match_all": {}
                }
            ]
        }
    },
    "from": 0,
    "size": 0,
    "aggregations": {
        "COUNT(distinct (mid))": {
            "cardinality": {
                "field": "(mid)"
            }
        }
    }
}
```
### 全文搜索
```
{
    "query" : {
        "query_string" : {"query" : "name:rcx"}
    }
}
```
### match查询
```
{
    "query": {
        "match": {
            "title": "crime and punishment"
        }
    }
}
```
### 通配符查询
```
{
    "query": {
        "wildcard": {
             "title": "cr?me"
        }
    }
}
```
### 范围查询
```
{
    "query": {
        "range": {
             "year": {
                  "gte" :1890,
                  "lte":1900
              }
        }
    }
}
```
### 正则表达式查询
```
{
    "query": {
        "regexp": {
             "title": {
                  "value" :"cr.m[ae]",
                  "boost":10.0
              }
        }
    }
}
```
### 布尔查询
```
{
    "query": {
        "bool": {
            "must": {
                "term": {
                    "title": "crime"
                }
            },
            "should": {
                "range": {
                    "year": {
                        "from": 1900,
                        "to": 2000
                    }
                }
            },
            "must_not": {
                "term": {
                    "otitle": "nothing"
                }
            }
        }
    }
}
```

## 更新

```http
index111/_doc/_30016/_update
{
  "doc": {
    "follow_status": "following"
  }
}
```

