ARRAY8 a1@@RANDOM_ID_1@@ 4
ARRAY(CREATE8, 4, a1@@RANDOM_ID_1@@)
ARRAY_WRITE(a1@@RANDOM_ID_1@@, 0, 1)
ARRAY_WRITE(a1@@RANDOM_ID_1@@, 1, 73)


ARRAY8 ans@@RANDOM_ID_2@@ 8
ARRAY(CREATE8, 8, ans@@RANDOM_ID_2@@)


DATA8 tmp@@RANDOM_ID_3@@
DATA32 tmp32@@RANDOM_ID_4@@
INPUT_DEVICE(SETUP, 0, @@PORT@@, 1, 0, 2, @a1@@RANDOM_ID_1@@, 8, @ans@@RANDOM_ID_2@@)


DATA32 size@@RANDOM_ID_5@@
ARRAY(SIZE, @@VARIABLE@@, size@@RANDOM_ID_5@@)
JR_GT32(size@@RANDOM_ID_5@@, 255, m@@RANDOM_ID_6@@)
ARRAY(DELETE, @@VARIABLE@@)
ARRAY(CREATE32, 8, @@VARIABLE@@)
m@@RANDOM_ID_6@@:

ARRAY_READ(ans@@RANDOM_ID_2@@, 0, tmp@@RANDOM_ID_3@@)
MOVE8_32(tmp@@RANDOM_ID_3@@, tmp32@@RANDOM_ID_4@@)
ARRAY_WRITE(@@VARIABLE@@, 0, tmp32@@RANDOM_ID_4@@)

ARRAY_READ(ans@@RANDOM_ID_2@@, 1, tmp@@RANDOM_ID_3@@)
MOVE8_32(tmp@@RANDOM_ID_3@@, tmp32@@RANDOM_ID_4@@)
ARRAY_WRITE(@@VARIABLE@@, 1, tmp32@@RANDOM_ID_4@@)

ARRAY_READ(ans@@RANDOM_ID_2@@, 2, tmp@@RANDOM_ID_3@@)
MOVE8_32(tmp@@RANDOM_ID_3@@, tmp32@@RANDOM_ID_4@@)
ARRAY_WRITE(@@VARIABLE@@, 2, tmp32@@RANDOM_ID_4@@)

ARRAY_READ(ans@@RANDOM_ID_2@@, 3, tmp@@RANDOM_ID_3@@)
MOVE8_32(tmp@@RANDOM_ID_3@@, tmp32@@RANDOM_ID_4@@)
ARRAY_WRITE(@@VARIABLE@@, 3, tmp32@@RANDOM_ID_4@@)

ARRAY_READ(ans@@RANDOM_ID_2@@, 4, tmp@@RANDOM_ID_3@@)
MOVE8_32(tmp@@RANDOM_ID_3@@, tmp32@@RANDOM_ID_4@@)
ARRAY_WRITE(@@VARIABLE@@, 4, tmp32@@RANDOM_ID_4@@)

ARRAY_READ(ans@@RANDOM_ID_2@@, 5, tmp@@RANDOM_ID_3@@)
MOVE8_32(tmp@@RANDOM_ID_3@@, tmp32@@RANDOM_ID_4@@)
ARRAY_WRITE(@@VARIABLE@@, 5, tmp32@@RANDOM_ID_4@@)

ARRAY_READ(ans@@RANDOM_ID_2@@, 6, tmp@@RANDOM_ID_3@@)
MOVE8_32(tmp@@RANDOM_ID_3@@, tmp32@@RANDOM_ID_4@@)
ARRAY_WRITE(@@VARIABLE@@, 6, tmp32@@RANDOM_ID_4@@)

ARRAY_READ(ans@@RANDOM_ID_2@@, 7, tmp@@RANDOM_ID_3@@)
MOVE8_32(tmp@@RANDOM_ID_3@@, tmp32@@RANDOM_ID_4@@)
ARRAY_WRITE(@@VARIABLE@@, 7, tmp32@@RANDOM_ID_4@@)

ARRAY(DELETE, ans@@RANDOM_ID_2@@)
ARRAY(DELETE, a1@@RANDOM_ID_1@@)