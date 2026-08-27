-- 조회수가 가장 높은 중고거래 게시물에 대한
-- 첨부파일 경로 조화
-- 파일 id기준 내림차순 정렬
-- 게시글 기준으로 id분리, 파일 이름은 id, 파일 이름, 파일 확장자로 구성 출력

SELECT CONCAT('/home/grep/src/', ud.board_id, '/',uf.file_id,uf.file_name,uf.file_ext) as FILE_PATH
FROM USED_GOODS_BOARD as ud JOIN USED_GOODS_FILE as uf
ON ud.board_id = uf.board_id
where ud.views IN (
    select max(views)
    from used_goods_board
)
ORDER BY uf.file_id desc