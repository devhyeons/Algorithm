# Write your MySQL query statement below

with first as (select 
rank() over(
    partition by product_id
    order by year 
) as ranks,
product_id,
year,
quantity,
price
from sales
)

select product_id,
year as first_year,
quantity,
price
from first 
where ranks = 1 