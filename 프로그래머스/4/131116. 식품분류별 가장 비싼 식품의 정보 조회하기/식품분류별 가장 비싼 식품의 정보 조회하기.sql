-- 가격이 제일 비판 식품의
-- 분류, 가격,이름 조회 SQL
-- 분류가 '과자','국','김치','식용유'인 경우만 출력
-- 식품 가격 기준 내림차순
SELECT CATEGORY, price as max_price, product_name
FROM FOOD_PRODUCT
WHERE (category, price) in (
    select category, max(price)
    from food_product
    where category in ( '과자', '국', '김치', '식용유')
    group by category
)
ORDER BY PRICE DESC
-- GROUP BY를 category로 진행한 뒤 max(price) 하면
-- cateogry에 따른 max price는 나오지만, product_name 은 groupby되지 않아서 
-- max가 아닌 price가 product_name에 매칭되는 문제가 발생.
-- 따라서 서브쿼리로 만든 뒤, 여기에 product_name 추가