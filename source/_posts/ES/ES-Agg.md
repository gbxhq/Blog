使用cate去聚合

```http
{
  "size": 0,
  "aggs": {
    "group_by_tags": {
      "terms": {
        "field": "cate",
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

