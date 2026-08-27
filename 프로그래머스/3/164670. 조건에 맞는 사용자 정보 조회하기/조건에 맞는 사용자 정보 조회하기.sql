--  중고거래 게시물 3건 이상 등록한 사용자 id, 닉네임, 전체주소, 전화번호 조회 SQL
-- 시, 도로명주소, 상세주소 함께 출력
-- 전화번호는 format 맞춰서.. 하이픈 삽입 출력
-- 회원 id기준 내림차순 
SELECT distinct(uu.user_id), uu.nickname, CONCAT(uu.city, ' ', uu.street_address1, ' ', uu.street_address2) as '전체주소',
CONCAT(substr(uu.tlno,1,3), '-', substr(uu.tlno,4,4),'-',substr(uu.tlno,8,4)) as '전화번호'
FROM USED_GOODS_BOARD as ub JOIN USED_GOODS_USER as uu
ON ub.writer_id = uu.user_id
where ub.writer_id IN  (
    SELECT writer_id
    from used_goods_board
    group by writer_id
    having count(*) >= 3
)
Order by ub.writer_id desc