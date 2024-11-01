#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAT_DTYPE float
#define MAT_AT(m, r, c) (m).data[(r)*(m).cols + (c)]
#define MAT_PRINT(m) mat_print(m, #m)

typedef struct {
  size_t rows;
  size_t cols;
  MAT_DTYPE *data ;
} Mat;

Mat mat_alloc(size_t rows, size_t cols);
void mat_add(Mat dst, Mat b);
void mat_mul(Mat dst, Mat a, Mat b);
void mat_fill(Mat m, MAT_DTYPE val);
void mat_print(Mat m, const char* name);

int main(void)
{
  Mat m1 = mat_alloc(1, 3);
  mat_fill(m1, 1);
  MAT_PRINT(m1);

  Mat m2 = mat_alloc(3, 2);
  mat_fill(m2, 1);
  MAT_PRINT(m2);

  Mat m3 = mat_alloc(1, 2);
  mat_mul(m3, m1, m2);
  MAT_PRINT(m3);
}

Mat mat_alloc(size_t rows, size_t cols)
{
  Mat m;
  m.rows = rows;
  m.cols = cols;
  m.data = (MAT_DTYPE*)malloc(rows*cols*sizeof(MAT_DTYPE));
  assert(m.data != NULL);
  return m;
}


void mat_add(Mat dst, Mat b) 
{
  assert(dst.rows == b.rows);
  assert(dst.cols == b.cols);
  for (size_t r = 0; r < b.rows; r++) {
    for (size_t c = 0; c < b.cols; c++) {
      MAT_AT(dst, r, c) += MAT_AT(b, r, c);
    }
  }
}


void mat_mul(Mat dst, Mat a, Mat b)
{
  // [W x Y] * [Y x Z] = [W x Z]
  assert(a.cols == b.rows);
  assert(dst.rows == a.rows);
  assert(dst.cols == b.cols);
  for (size_t r = 0; r < dst.rows; r++) {
    for (size_t c = 0; c < dst.cols; c++) {
      MAT_AT(dst, r, c) = 0;
      for (size_t i = 0; i < a.cols; i++) {
        MAT_AT(dst, r, c) += MAT_AT(a, r, i) * MAT_AT(b, i, c);
      }
    }
  }
}


void mat_fill(Mat m, MAT_DTYPE val)
{
  for (size_t r = 0; r < m.rows; r++) {
    for (size_t c = 0; c < m.cols; c++) {
      MAT_AT(m, r, c) = val;
    }
  }
}


void mat_print(Mat m, const char* name)
{
  printf("%s=[\n", name);
  for (size_t r = 0; r < m.rows; r++) {
    printf("  ");
    for (size_t c = 0; c < m.cols; c++) {
      printf("%f  ", MAT_AT(m, r, c));
    }
    printf("\n");
  }
  printf("]\n");
}
