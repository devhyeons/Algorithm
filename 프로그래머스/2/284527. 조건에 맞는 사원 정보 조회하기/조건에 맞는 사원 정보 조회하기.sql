-- * 꼭 다시 풀어보기 (25-07-02)
-- 2022년도 한해 평가 점수 가장 높은 사원 정보 조회
-- 가장 높은 사원들의 점수, 사번, 성명, 직책, 이메일 조회
-- 평가 점수 = (상 + 하반기 점수), 평가 점수 as SCORE

# WITH E_SCORE as (
#     SELECT he.emp_no, sum(hg.score) as score 
#     FROM HR_EMPLOYEES as he JOIN HR_GRADE as hg
#     ON he.emp_no = hg.emp_no
#     WHERE hg.year = '2022'
#     GROUP BY he.emp_no
#     ORDER BY sum(hg.score) DESC
# ), MAX_SCORE as (
#     SELECT max(score)
#     FROM E_SCORE
# )

# SELECT sum(hg.score) as SCORE,
# he.emp_no as EMP_NO,
# he.emp_name as EMP_NAME,
# he.position as POSITION,
# he.email as EMAIL
# FROM HR_EMPLOYEES as he JOIN HR_GRADE as hg
# ON he.emp_no = hg.emp_no
# GROUP BY he.emp_no, he.emp_name, he.position, he.email
# HAVING sum(hg.score) = (
#        SELECT max(score)
#        FROM E_SCORE
# )

-- 새로운 풀이
WITH E_SCORE AS (
  SELECT
    hg.emp_no,
    SUM(hg.score) AS score
  FROM HR_GRADE hg
  WHERE hg.year = '2022'
  GROUP BY hg.emp_no
),
MAX_SCORE AS (
  SELECT MAX(score) AS max_score
  FROM E_SCORE
)
SELECT
  es.score    AS SCORE,
  he.emp_no   AS EMP_NO,
  he.emp_name AS EMP_NAME,
  he.position AS POSITION,
  he.email    AS EMAIL
FROM E_SCORE es
JOIN MAX_SCORE ms
  ON es.score = ms.max_score
JOIN HR_EMPLOYEES he
  ON es.emp_no = he.emp_no;