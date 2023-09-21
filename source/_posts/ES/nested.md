---
title: ES nested 使用
date: 2020-01-19
categories: ElasticSearch
tags: [ElasticSearch,ES]
---


新建nested字段

```json
{
  "dynamic": "strict",
  "properties": {
      "aiop_tag": {
          "type": "nested",
          "properties": {
            "id": {
              "type": "long"
            },
            "option_id": {
              "type": "long"
            },
            "op_time": {
                "type": "integer"
            },
            "op_user": {
                "type": "keyword"
            }
          }
        }
  }
}
```



```json
{
"_source":["bid","aiop_tag"],
"track_total_hits":true,
  "query": {
    "bool": {
      "must": [
        {
          "nested": {
            "path": "aiop_tag",
            "query": {
              "bool": {
                "must": [
                  {
                    "term": {
                      "aiop_tag.option_id": "408"
                    }
                  }
                ],
                "must_not": [],
                "should": []
              }
            }
          }
        }
      ],
      "must_not": [],
      "should": []
    }
  },
  "from": 0,
  "size": 10,
  "sort": [],
  "aggs": {}
}
```

