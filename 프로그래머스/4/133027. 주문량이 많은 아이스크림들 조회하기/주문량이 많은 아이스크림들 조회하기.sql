-- 7월 총 주문량과 상반기 총 주문량 더한값 큰 순
-- 상위 3개 맛 조회 --> 

SELECT f.flavor as flavor
FROM FIRST_HALF as f JOIN JULY as j
ON f.flavor = j.flavor
group by f.flavor
order by sum (f.total_order) + sum (j.total_order) desc
limit 3;