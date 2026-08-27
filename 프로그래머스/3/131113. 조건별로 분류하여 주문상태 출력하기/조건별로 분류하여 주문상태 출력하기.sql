-- food_order에서 2022-05-02기준 출고 일자, 출고여부 조회
-- 이후 날짜는 출고 대기, 미정은 출고 미정,
-- 주문 id기준 오름차순
SELECT order_id, product_id, date_format(out_date, '%Y-%m-%d') as out_date,
Case
WHEN date_format(out_date, '%Y-%m-%d') <= '2022-05-02'THEN '출고완료'
WHEN date_format(out_date, '%Y-%m-%d') > '2022-05-02' THEN '출고대기'
ELSE '출고미정'
END as '출고여부'
from food_order
order by order_id asc