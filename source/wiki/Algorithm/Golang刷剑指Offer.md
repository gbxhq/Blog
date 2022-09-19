
## 43 1出现的次数
```go
func countDigitOne(n int) int {
   sum := 0
   last := 0
   this := 0
   weight := 1
   for n > 0 {
      // 每一位出现 1 的个数，都至少是他前面的数字
      // 比如 123 这个数字，个位 1 出现的个数，至少有 12 次（对应0-11这12种情况，当前面是 12 时的情况要单独算）
      sum += n / 10 * weight
      // 加完它前面的数字，再根据这一位分析还会出现几次
      this = n % 10
      // 这时候要分 3 种情况了
      switch this {
      // 0 的时候说明第 13 轮这里不会再出现 1
      case 0:
         sum += 0
      // 1 的时候出现几个 1，要看它后面的数字，比如123，百位=1，百位出现1的次数=24(0~23是 24 次）
      case 1:
         sum += last + 1
      // 大于 1 的时候出现的次数就是权重，比如123，十位=2，大于 1，则第二位 1 的次数是 10
      default:
         sum += weight
      }
      last += this * weight
      weight *= 10
      n /= 10
   }
   return sum
}
```