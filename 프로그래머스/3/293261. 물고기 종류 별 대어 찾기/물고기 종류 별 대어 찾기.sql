-- 종류별 가장 큰 물고기의 Id, 이름, 길이 출력
-- 물고기 id에 대한 asc

SELECT FI.ID, FN.FISH_NAME as FISH_NAME, FI.LENGTH
FROM FISH_INFO as FI JOIN FISH_NAME_INFO as FN
ON FI.FISH_TYPE = FN.FISH_TYPE
JOIN (
    SELECT FISH_TYPE, MAX(LENGTH) as MAX_LEN
    FROM FISH_INFO
    GROUP BY FISH_TYPE
) AS MAX_INFO 
ON FI.FISH_TYPE = MAX_INFO.FISH_TYPE AND FI.LENGTH = MAX_INFO.MAX_LEN
ORDER BY FI.ID ASC


-- 처음 고치기 전 답이 틀린 이유
-- 좋아, 정확히 짚어줄게! 👀
# 너가 쓴 이 쿼리:

# sql
# 코드 복사
# SELECT FI.ID, FN.FISH_NAME AS FISH_NAME, FI.LENGTH
# FROM FISH_INFO AS FI 
# JOIN FISH_NAME_INFO AS FN ON FI.FISH_TYPE = FN.FISH_TYPE
# WHERE (FI.FISH_TYPE, FI.LENGTH) = (
#     SELECT FISH_TYPE, MAX(LENGTH)
#     FROM FISH_INFO
#     GROUP BY FISH_TYPE
# )
# ORDER BY FI.ID ASC;
# 문법은 얼핏 맞아보이는데, 이게 틀린 이유가 분명해.

# ❗ 문제점 1.
# WHERE (FI.FISH_TYPE, FI.LENGTH) = (서브쿼리) 이 부분에서

# ✅ (컬럼 2개) = (SELECT) 는 원래 불가능해.

# MySQL, SQL 표준 모두

# (컬럼1, 컬럼2) = (SELECT ...)
# 이렇게 바로 비교하는 걸 허용하지 않아.

# 서브쿼리는 반드시 "1개 컬럼 1개 값"만 반환해야 해.

# 여기서는 FISH_TYPE별로 여러 개 ROW를 반환하기 때문에
# = (단일 값) 비교 자체가 아예 안 된다.

# 즉,

# (컬럼, 컬럼) = (SELECT ...) 자체가 SQL 문법 위배야.

# 그리고 GROUP BY를 했기 때문에 SELECT 결과가 여러 줄이라 단일 비교 불가능해.