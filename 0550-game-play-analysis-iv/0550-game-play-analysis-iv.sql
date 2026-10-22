# Write your MySQL query statement below

-- 첫 다음날 다시 로그인한 플레이어의 비율
-- 소수점 둘째자리까지 반올림 

WITH firstLogin as (
    SELECT player_id, min(event_date) as first_date
    FROM Activity as a
    group by player_id
)

SELECT ROUND(SUM(
    CASE
    WHEN EXISTS (
        SELECT 1
        FROM firstLogin as f
        WHERE a.player_id = f.player_id
        AND a.event_date = DATE_ADD(f.first_date, INTERVAL 1 DAY)
    )then 1
    ELSE 0
    END 
) / COUNT(distinct player_id), 2) as fraction
FROM Activity as a