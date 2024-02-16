# false

- mapping 里没有 A 字段

这时候我更行用户1 的 doc 的时候，传入了 A 字段

这时候查询doc，会发现，可以查出 A 字段的值。但 A 并不能被搜索。

- 新建 mapping，加入 A 字段

这时候再去搜 A，会发现，原来已有 A 字段的 doc 用户1 还是不会被搜出来。

这时用户2新增 A 字段的，是可以搜出来的用户2的。

- 请求ES，更新用户1 的A 字段，但是值不变

还是搜不出来。

其实是因为值不变没有导致 doc 的版本更新

- 请求ES，更新用户1 的A 字段，但是值不变

终于可以通过 A 字段查到用户1了

## 结论

- false 时，未知字段无法索引
- 给未知字段新建 mapping 后，已经存在该字段的文档不会被搜出
- 所有文档更新后，可以被搜索。但是值一定要改变才行。所以建议给新建字段后，把存量有字段的 doc 全部删掉，再统一更新一次。

# 插件

## 中文

[简体中文语言包 - Flarum 中文社区](https://discuss.flarum.org.cn/d/1211)

```
composer require flarum-lang/chinese-simplified
php flarum cache:clear
```
