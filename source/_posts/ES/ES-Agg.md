---
title: ES Agg 聚合
date: 2020-01-19
categories: ElasticSearch
tags: [ElasticSearch,ES]
---


使用cate去聚合

```http
{
  "size": 0,
  "aggs": {
    "group_by_tags": {
      "terms": {
        "field": "cat",
        "size": 50
      }
    }
  }
}
```



```http
{
  "size": 0,
  "aggs": {
    "sum_monthly_bs_total": {
      "sum": {
        "field": "total_fans"
      }
    }
  }
}
```


sum 时增加判断条件

```json
{
  "query": {
    "bool": {
      "must": [
        {
          "term": {
            "is_mcn": 0
          }
        },
        {
          "term": {
            "event_day": 20221111
          }
        }
      ]
    }
  },
  "aggs": {
    "all_is_active": {
      "sum": {
        "field": "all_is_active"
      }
    },
    "all_is_active_month": {
      "sum": {
        "field": "all_is_active_month"
      }
    },
    "all_author_distribution_avg": {
      "sum": {
        "script": {
          "lang": "painless",
          "source": "doc['all_author_distribution_avg'].value<1000? 1: 0"
        }
      }
    },
    "all_author_distribution_avg2": {
      "sum": {
        "script": {
          "lang": "painless",
          "source": "doc['all_author_distribution_avg'].value>8000? 1: 0"
        }
      }
    }
  },
  "size": 0,
  "track_total_hits": true
}
```

