#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_SINH_VIEN 100
#define MAX_MON 100
typedef struct{
    char maSV[20];
    char hoTen[100];
    int soMon;
    double diem[MAX_MON];
    double diemTB;
    char xepLoai[20];
	} SinhVien;
	void xoaBND() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
	}
/* ================================
   NHAP DIEM
   ================================ */
	double nhapDiem(int thuTu) {
    double diem;
    int ketQua;
    while (1) {
    	printf("Nhap diem mon %d: ", thuTu);
        ketQua = scanf("%lf", &diem);
    if (ketQua != 1) {
        printf("Vui long nhap so!\n");
        xoaBND(); }
    else if (diem < 0 || diem > 10) {
        printf("Diem phai tu 0 den 10!\n");
        xoaBND();
    } else {
        xoaBND();
    return diem;
    }
    }
	}
/* ================================
   NHAP SO MON
   ================================ */
	int nhapSoMon() {
    int soMon;
    int ketQua;
    while (1) {
        printf("Nhap so luong mon hoc: ");
        ketQua = scanf("%d", &soMon);
    if (ketQua != 1) {
        printf("Vui long nhap so nguyen!\n");
        xoaBND();
    } else if (soMon <= 0 || soMon > MAX_MON) {
        printf("So mon phai tu 1 den %d!\n",MAX_MON);
        xoaBND();
    } else {
        xoaBND();
    return soMon;
    }
    }
    }
/* ================================
   TINH DIEM TRUNG BINH
   ================================ */
	double tinhDiemTB(SinhVien sv) {
    double tong = 0;
    int i;
    for (i = 0; i < sv.soMon; i++) {
        tong = tong + sv.diem[i];
    }
    return tong / sv.soMon;
	}
/* ================================
   XEP LOAI
   ================================ */
	void xepLoai(
    double diemTB,
    char xepLoaiSV[]
	)
    {
    if (diemTB >= 8.0) {
        strcpy(xepLoaiSV, "Gioi");
    } else if (diemTB >= 6.5) {
        strcpy(xepLoaiSV, "Kha");
    } else if (diemTB >= 5.0) {
        strcpy(xepLoaiSV, "Trung binh");
    } else {
        strcpy(xepLoaiSV, "Yeu");
    }
    }
/* ================================
   NHAP 1 SINH VIEN
   ================================ */
	void nhapSinhVien(SinhVien *sv) {
    int i;
    printf("\n===== NHAP THONG TIN SINH VIEN =====\n");
    printf("Nhap ma sinh vien: ");
    scanf("%19s", sv->maSV);
    xoaBND();
    printf("Nhap ho ten: ");
    fgets(
        sv->hoTen,
        sizeof(sv->hoTen),
        stdin
    );
    sv->hoTen[
        strcspn(sv->hoTen, "\n")
    ] = '\0';
    sv->soMon = nhapSoMon();
    for (i = 0; i < sv->soMon; i++)
    {
        sv->diem[i] = nhapDiem(i + 1);
    }
    sv->diemTB = tinhDiemTB(*sv);
	xepLoai(
        sv->diemTB,
        sv->xepLoai
    );
	}
/* ================================
   IN 1 SINH VIEN
   ================================ */
void inThongTin(SinhVien sv) {
    int i;
    printf("\n===== THONG TIN SINH VIEN =====\n");
    printf("Ma sinh vien: %s\n",sv.maSV);
    printf("Ho ten: %s\n",sv.hoTen);
    printf("So mon: %d\n",sv.soMon);
    printf("Diem:");
    for (i = 0; i < sv.soMon; i++){
        printf(" %.2f",sv.diem[i]);
    }
    printf("\n");
    printf("Diem trung binh: %.2f\n", sv.diemTB);
    printf("Xep loai: %s\n",sv.xepLoai);
	}
/* ================================
   TIM SINH VIEN THEO MA
   ================================ */
	int timViTri(
    SinhVien danhSach[],
    int soLuong,
    char maCanTim[] )
	{
    int i;
    for (i = 0; i < soLuong; i++)  {
    if (strcmp(danhSach[i].maSV,maCanTim) == 0)
    {
    return i;
    }
    }
    return -1;
	}
/* ================================
   THEM SINH VIEN
   ================================ */
	void themSinhVien(
    SinhVien danhSach[],
    int *soLuong) {
    SinhVien sv;
    int viTri;
    if (*soLuong >= MAX_SINH_VIEN) {
    printf("\nLop da day!\n");
    return;
    }
    nhapSinhVien(&sv);
    viTri = timViTri(danhSach,*soLuong,sv.maSV);
    if (viTri != -1) {
    printf("\nMa %s da ton tai!\n",sv.maSV);
    return;
    }
    danhSach[*soLuong] = sv;(*soLuong)++;
    printf("\nThem sinh vien thanh cong!\n");
    printf("Si so hien tai: %d\n",*soLuong);
	}
/* ================================
   IN DANH SACH
   ================================ */
	void inDanhSach(
    SinhVien danhSach[],
    int soLuong)
	{
    int i;
    if (soLuong == 0){
        printf("\nDanh sach trong!\n");
    return;
    }
    printf("\n========== DANH SACH SINH VIEN ==========\n");
    for (i = 0; i < soLuong; i++) {
    printf("\n----- SINH VIEN %d -----\n",i + 1);
    inThongTin(danhSach[i]);
    }
	}
/* ================================
   TIM SINH VIEN
   ================================ */
	void timSinhVien(
    SinhVien danhSach[],
    int soLuong)
	{
    char maCanTim[20];
    int viTri;
    if (soLuong == 0) {
    printf("\nDanh sach trong!\n");
    return;
    }
    printf("\nNhap ma sinh vien can tim: ");
    scanf("%19s",maCanTim);
    xoaBND();
    viTri = timViTri(danhSach,soLuong,maCanTim);
    if (viTri == -1) {
    printf("\nKhong tim thay!\n");
    } else {
    printf("\nTim thay sinh vien:\n");
    inThongTin(danhSach[viTri]);
    }
	}
/* ================================
   HOAN DOI
   ================================ */
	void hoanDoi(SinhVien *sv1,SinhVien *sv2)
	{
    SinhVien temp;
    temp = *sv1;
	*sv1 = *sv2;
    *sv2 = temp;
	}
/* ================================
   SAP XEP
   ================================ */
	void sapXep(
    SinhVien danhSach[],
    int soLuong)
	{
    int i;
    int j;
    if (soLuong == 0){
    printf("\nDanh sach trong!\n");
	 return;
    }
    for (i = 0; i < soLuong - 1; i++){
    for (j = i + 1; j < soLuong; j++){
    if (danhSach[i].diemTB < danhSach[j].diemTB) {
    hoanDoi(&danhSach[i],&danhSach[j]);
	} else if (danhSach[i].diemTB == danhSach[j].diemTB) {
	if (strcmp(danhSach[i].hoTen,danhSach[j].hoTen) > 0) {
    hoanDoi(&danhSach[i],&danhSach[j]);
    }
    }
    }
    }
    printf("\nDa sap xep thanh cong!\n");
	}
/* ================================
   XUAT BAO CAO RA FILE
   ================================ */
	void xuatBaoCao(SinhVien danhSach[],int soLuong)
   {
    FILE *file;
    int i;
    int j;
    int gioi = 0;
    int kha = 0;
    int trungBinh = 0;
    int yeu = 0;
    if (soLuong == 0) {
    printf("\nDanh sach trong!\n");
    return;
    }
    /*
        Mo file bang "w"
        => ghi de noi dung cu
    */
    file = fopen("bao_cao.txt","w");
    if (file == NULL) {
    	printf("\nKhong mo duoc file!\n");
    return;
    }
    fprintf(file,"========== BAO CAO DIEM SINH VIEN ==========\n\n");
    for (i = 0; i < soLuong; i++){
     fprintf(file,"%d. %s - %s\n",i + 1,danhSach[i].maSV,danhSach[i].hoTen);
     fprintf(file,"Diem: ");
    for (j = 0;j < danhSach[i].soMon;j++)
    {
     fprintf(file,"%.2f ",danhSach[i].diem[j]);
    }
     fprintf(file,"\nDiem TB: %.2f\n",danhSach[i].diemTB);
     fprintf(file,"Xep loai: %s\n\n",danhSach[i].xepLoai);
    if (strcmp(danhSach[i].xepLoai,"Gioi") == 0) {
        gioi++;
    } else if (strcmp(danhSach[i].xepLoai,"Kha") == 0) {
        kha++;
    }else if (strcmp(danhSach[i].xepLoai,"Trung binh") == 0) {
        trungBinh++;
    } else { yeu++;}
    }
    fprintf(file,"========== THONG KE ==========\n");
    fprintf(file,"Gioi: %d, Kha: %d, TB: %d, Yeu: %d\n",gioi,kha,trungBinh,yeu);
    fclose(file);
    printf("\nXuat bao cao thanh cong!\n" );
    printf("File: bao_cao.txt\n");
	}
/* ================================
   MAIN
   ================================ */
	int main() {
    SinhVien danhSach[MAX_SINH_VIEN];
    int soLuong = 0;
    int luaChon;
    do {printf("\n\n");
	printf("====================================\n");
    printf("       QUAN LY DIEM SINH VIEN\n");
	printf("====================================\n");
    printf("1. Them sinh vien\n");
    printf("2. In danh sach sinh vien\n");
    printf("3. Tim sinh vien theo ma\n");
    printf("4. Sap xep theo diem trung binh\n");
	printf("5. Xuat bao cao ra file\n");
    printf("0. Thoat\n");
    printf("====================================\n");
	printf("Chon chuc nang: ");
    if (scanf("%d",&luaChon) != 1){
        printf("Vui long nhap so!\n");
        xoaBND();
    continue;
    }
        xoaBND();
    switch (luaChon) {
    	case 1:themSinhVien(danhSach, &soLuong);
        break;
        case 2:inDanhSach(danhSach,soLuong);
        break;
        case 3:timSinhVien(danhSach,soLuong);
        break;
    	case 4:sapXep(danhSach,soLuong);
        break;
        case 5:xuatBaoCao(danhSach,soLuong);
        break;
        case 0:
        printf("\nThoat chuong trinh.\n");
        break;
    	default:
        printf("\nLua chon khong hop le, ""vui long thu lai!\n");
    	break;
    }
    }
    while (luaChon != 0);
    return 0;
}
