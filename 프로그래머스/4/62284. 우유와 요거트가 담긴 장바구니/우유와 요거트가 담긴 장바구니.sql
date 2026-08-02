-- 우유, 요거트 동시 구입 장바구니 조회
-- 장바구니 아이디 ASC 

WITH CNT as (
SELECT CART_ID, COUNT(DISTINCT c.NAME) as total
FROM CART_PRODUCTS as C
WHERE c.NAME IN ('Yogurt', 'Milk')
GROUP BY CART_ID
)

SELECT  c.CART_ID as CART_ID
FROM CNT as c
WHERE c.total = 2
ORDER BY c.CART_ID ASC