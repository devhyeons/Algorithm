# Write your MySQL query statement below
-- 고객이 지불한 금액의 7일 이동평균을 계산. (현재날짜 + 6일전)
-- average_amount는 소수점 둘째자리로 반올림
-- visited_on ASC로 정렬

WITH daily as (
    SELECT visited_on, SUM(amount) as amount
    FROM customer
    Group by visited_on
),
moving as (
    SELECT visited_on,
    SUM(amount) OVER (
        ORDER BY visited_on
        ROWS BETWEEN 6 PRECEDING AND CURRENT ROW
    ) as amount,
    ROW_NUMBER() OVER(
        ORDER BY visited_on
    ) as rn 
    FROM daily
)

SELECT visited_on, amount, ROUND(amount/7, 2) as average_amount
FROM moving 
WHERE rn >= 7
ORDER BY visited_on ASC