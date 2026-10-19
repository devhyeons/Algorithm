# Write your MySQL query statement below
-- 고객이 방문은 했지만 어떤 거래도 하지 않은 경우

SELECT v.customer_id, count(*) as count_no_trans
FROM Visits as v LEFT JOIN Transactions as t
on v.visit_id = t.visit_id
WHERE t.transaction_id IS NULL
GROUP BY v.customer_id