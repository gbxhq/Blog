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
  "query": {
    "bool": {
      "must": [
        {
          "nested": {
            "path": "new_tag",
            "query": {
              "bool": {
                "must": [
                  {
                    "term": {
                      "new_tag.id": "666"
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

