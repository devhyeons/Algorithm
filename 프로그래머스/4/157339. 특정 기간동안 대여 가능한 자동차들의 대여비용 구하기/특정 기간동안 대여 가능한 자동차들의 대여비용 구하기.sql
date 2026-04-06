-- 세단 or SUV중에
-- 2022-11-01~ 11-30 까지 대여 가능하고
-- 30일간 대여 금액 50만원 <= x <= 200만원 미만 

-- 자동차 ID, 종류, 대여금액 리스트 출력
-- 대여금액 기준 ASC
-- 종류 ASC, 자동차 ID DESC 

WITH AVAIL as (
    SELECT h.car_id, c.car_type, c.daily_fee
    FROM CAR_RENTAL_COMPANY_RENTAL_HISTORY as h 
    JOIN CAR_RENTAL_COMPANY_CAR as c
    ON h.car_id = c.car_id
    WHERE c.car_type IN ('SUV', '세단')
    AND h.car_id NOT IN (
        SELECT car_id
        FROM CAR_RENTAL_COMPANY_RENTAL_HISTORY
        WHERE start_date <= '2022-11-30'
          AND end_date >= '2022-11-01'
    )
)

SELECT distinct a.car_id as car_id,
a.car_type as car_type,
TRUNCATE((30 * (a.daily_fee * (1- (p.discount_rate/100)))),0) as fee
FROM avail as a JOIN CAR_RENTAL_COMPANY_DISCOUNT_PLAN as p
ON a.car_type = p.car_type
WHERE p.duration_type = '30일 이상' 
AND (30 * (a.daily_fee * (1- (p.discount_rate/100)))) >= 500000 
AND (30 * (a.daily_fee * (1- (p.discount_rate/100)))) < 2000000
ORDER BY a.daily_fee * (1- (p.discount_rate/100)) DESC,
a.car_type ASC,
a.car_id DESC

