class Solution {
    fun solution(n: Int, lost: IntArray, reserve: IntArray): Int {

        var reserveLost  = 0
        var reserveVar  = reserve.sorted().toIntArray()
        var lostVar = lost.sorted().toIntArray()
        
       lostVar.forEachIndexed{ index, it ->
            for (i in reserveVar.indices){
                if (it == reserveVar[i]){
                    reserveVar[i] = -1
                    lostVar[index] = -1
                    reserveLost++
                }
            }
        } //여분을 잃어버린 경우
        
        var answer = n - lostVar.size + reserveLost
        println(answer)
        
        reserveVar.forEach {
            val plus = it + 1
            val minus = it - 1
            var flag = 0
            println("$plus , $minus")
            for (i in lostVar.indices) {
                println(lostVar[i])
                if (flag == 0) {
                    if (lostVar[i] == plus) {
                        flag = 1
                        lostVar[i] = -1
                        answer++
                        println("plus 동일")
                    } else if (lostVar[i] == minus) {
                        flag = 1
                        lostVar[i] = -1
                        answer++
                        println("minus 동일")
                    }
                }
            }
        }
        return answer
    }
}