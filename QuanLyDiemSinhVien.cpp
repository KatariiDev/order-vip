
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>

#define MAX_SINH_VIEN 1000
#define MAX_MSSV 8
#define MAX_TEN 100
#define MAX_TEN_MON 30

typedef struct {
    char maSV[MAX_MSSV + 1];
    char hoTen[MAX_TEN];
    char tenMon[MAX_TEN_MON];
    double diem;
} SinhVien;

typedef struct {
    char maSV[MAX_MSSV + 1];
    char hoTen[MAX_TEN];
    double diemTB;
    char xepLoai[10];
} SinhVienTB;

/* ================= PROTOTYPE ================= */

void docDong(char chuoi[], int kichThuoc);
void xoaTrang(char chuoi[]);
int nhapSoNguyen(char thongBao[], int min, int max, int *giaTri);
int kiemTraLogic(SinhVien ds[], int n, SinhVien *sv, int loai);
int kiemTraDiem(char chuoi[], double *diem);
int coDiem(SinhVien ds[], int n);
void choNhap0(void);
void nhapSinhVien(SinhVien ds[], int *n, int *soSV);
void nhapDiem(SinhVien ds[], int *n);
void inBang(SinhVien ds[], int n, SinhVienTB dsTB[], int soSV, int loaiBang);
int taoDanhSachTB(SinhVien ds[], int n, SinhVienTB dsTB[]);
void sapXep(SinhVienTB dsTB[], int n);
void timSinhVien(SinhVien ds[], int n);
void locSinhVien(SinhVienTB dsTB[], int n);
void xuatFile(SinhVienTB dsTB[], int n);

/* ================= MAIN ================= */

int main(void) {
    SinhVien ds[MAX_SINH_VIEN] = {0};
    SinhVienTB dsTB[MAX_SINH_VIEN] = {0};

    int n = 0;
    int soSV = 0;
    int soSVTB = 0;
    int chon = 0;

    do {
        printf("\n========================================\n");
        printf("        QUAN LY DIEM SINH VIEN\n");
        printf("========================================\n");
        printf("1. Nhap sinh vien\n");
        printf("2. Nhap diem\n");
        printf("3. Sap xep\n");
        printf("4. Tim sinh vien\n");
        printf("5. Loc sinh vien\n");
        printf("6. Hien thi danh sach chi tiet\n");
        printf("7. Hien thi bang diem trung binh\n");
        printf("8. Xuat file\n");
        printf("0. Thoat\n");
        printf("========================================\n");

        nhapSoNguyen("Nhap lua chon (0 - 8): ", 0, 8, &chon);

        switch (chon) {
            case 1:
                nhapSinhVien(ds, &n, &soSV);
                break;

            case 2:
                if (soSV == 0) {
                    printf("\nChua co sinh vien! Hay nhap sinh vien truoc.\n");
                    break;
                }
                nhapDiem(ds, &n);
                break;

            case 3:
                if (!coDiem(ds, n)) {
                    printf("\nChua co diem sinh vien!\n");
                    break;
                }
                soSVTB = taoDanhSachTB(ds, n, dsTB);
                sapXep(dsTB, soSVTB);
                break;

            case 4:
                if (soSV == 0) {
                    printf("\nChua co sinh vien!\n");
                    break;
                }
                timSinhVien(ds, n);
                break;

            case 5:
                if (!coDiem(ds, n)) {
                    printf("\nChua co diem sinh vien!\n");
                    break;
                }
                soSVTB = taoDanhSachTB(ds, n, dsTB);
                locSinhVien(dsTB, soSVTB);
                break;

            case 6:
                if (!coDiem(ds, n)) {
                    printf("\nChua co diem sinh vien!\n");
                    break;
                }
                inBang(ds, n, NULL, 0, 1);
                choNhap0();
                break;

            case 7:
            	printf("\n========== BANG DIEM TRUNG BINH ==========\n");
                if (!coDiem(ds, n)) {
                    printf("\nChua co diem sinh vien!\n");
                    break;
                }
                soSVTB = taoDanhSachTB(ds, n, dsTB);
                inBang(NULL, 0, dsTB, soSVTB, 2);
                choNhap0();
                break;

            case 8:
                if (!coDiem(ds, n)) {
                    printf("\nChua co diem sinh vien!\n");
                    break;
                }
                soSVTB = taoDanhSachTB(ds, n, dsTB);
                xuatFile(dsTB, soSVTB);
                break;

            case 0:
                printf("\nDa thoat chuong trinh!\n");
                break;
        }
    } while (chon != 0);

    return 0;
}

/* Doc mot dong tu ban phim */
void docDong(char chuoi[], int kichThuoc) {
    int c = 0;

    if (fgets(chuoi, kichThuoc, stdin) == NULL) {
        chuoi[0] = '\0';
        return;
    }

    if (strchr(chuoi, '\n') == NULL) {
        while ((c = getchar()) != '\n' && c != EOF) {
        }
    }

    chuoi[strcspn(chuoi, "\n")] = '\0';
}

/* Xoa khoang trang o dau va cuoi chuoi */
void xoaTrang(char chuoi[]) {
    char *dau = chuoi;
    char *cuoi = NULL;

    while (*dau == ' ' || *dau == '\t')
        dau++;

    if (*dau == '\0') {
        chuoi[0] = '\0';
        return;
    }

    cuoi = dau + strlen(dau) - 1;

    while (cuoi >= dau && (*cuoi == ' ' || *cuoi == '\t')) {
        *cuoi = '\0';
        cuoi--;
    }

    if (dau != chuoi)
        memmove(chuoi, dau, strlen(dau) + 1);
}

/* Chi nhan chuoi gom cac chu so va nam trong khoang cho phep */
int nhapSoNguyen(char thongBao[], int min, int max, int *giaTri) {
    char buf[100] = "";
    char *ketThuc = NULL;
    long so = 0;
    int i = 0;
    int hopLe = 1;

    while (1) {
        printf("%s", thongBao);
        docDong(buf, sizeof(buf));

        if (buf[0] == '\0') {
            printf("  -> Khong duoc de trong!\n");
            continue;
        }

        hopLe = 1;

        for (i = 0; buf[i] != '\0'; i++) {
            if (!isdigit((unsigned char)buf[i])) {
                hopLe = 0;
                break;
            }
        }

        if (!hopLe) {
            printf("  -> Chi duoc nhap so nguyen!\n");
            continue;
        }

        so = strtol(buf, &ketThuc, 10);

        if (ketThuc == buf || *ketThuc != '\0' ||
            so < min || so > max) {
            printf("  -> Vui long nhap so nguyen tu %d den %d!\n",
                   min, max);
            continue;
        }

        *giaTri = (int)so;
        return 1;
    }
}

/* Chi cho phep nhap 0 de quay ve menu */
void choNhap0(void) {
    char buf[20] = "";

    printf("\nNhan 0 de quay ve menu: ");

    while (1) {
        docDong(buf, sizeof(buf));

        if (strcmp(buf, "0") == 0)
            break;

        printf("Chi duoc nhap 0: ");
    }
}

/* Kiem tra MSSV, ho ten, ten mon va diem */
int kiemTraLogic(SinhVien ds[], int n, SinhVien *sv, int loai) {
    int i = 0;
    int coChu = 0;
    int dai = 0;

    if (loai == 1) {
        dai = (int)strlen(sv->maSV);

        if (dai != MAX_MSSV) {
            printf("  -> MSSV phai co dung 8 chu so!\n");
            return 0;
        }

        for (i = 0; i < dai; i++) {
            if (!isdigit((unsigned char)sv->maSV[i])) {
                printf("  -> MSSV chi duoc chua chu so!\n");
                return 0;
            }
        }

        for (i = 0; i < n; i++) {
            if (strcmp(ds[i].maSV, sv->maSV) == 0) {
                printf("  -> MSSV nay da ton tai!\n");
                return 0;
            }
        }

        return 1;
    }

    if (loai == 2) {
        dai = (int)strlen(sv->hoTen);

        if (dai == 0 || dai >= MAX_TEN) {
            printf("  -> Ho ten khong duoc de trong hoac qua dai!\n");
            return 0;
        }

        coChu = 0;

        for (i = 0; sv->hoTen[i] != '\0'; i++) {
            unsigned char c = (unsigned char)sv->hoTen[i];

            if (c == ' ')
                continue;

            if (isalpha(c) || c >= 128)
                coChu = 1;
            else {
                printf("  -> Ho ten chi duoc chua chu cai va khoang trang!\n");
                return 0;
            }
        }

        if (!coChu) {
            printf("  -> Ho ten phai co chu cai!\n");
            return 0;
        }

        return 1;
    }

    if (loai == 3) {
        dai = (int)strlen(sv->tenMon);

        if (dai == 0 || dai >= MAX_TEN_MON) {
            printf("  -> Ten mon khong duoc de trong hoac qua dai!\n");
            return 0;
        }

        coChu = 0;

        for (i = 0; sv->tenMon[i] != '\0'; i++) {
            unsigned char c = (unsigned char)sv->tenMon[i];

            if (c == ' ' || isdigit(c))
                continue;

            if (isalpha(c) || c >= 128)
                coChu = 1;
            else {
                printf("  -> Ten mon chi duoc chua chu, so va khoang trang!\n");
                return 0;
            }
        }

        if (!coChu) {
            printf("  -> Ten mon phai co chu cai!\n");
            return 0;
        }

        for (i = 0; i < n; i++) {
            if (strcmp(ds[i].maSV, sv->maSV) == 0 &&
                ds[i].tenMon[0] != '\0' &&
                strcmp(ds[i].tenMon, sv->tenMon) == 0) {
                printf("  -> Sinh vien nay da co diem mon %s!\n",
                       sv->tenMon);
                return 0;
            }
        }

        return 1;
    }

    if (loai == 4) {
        if (sv->diem < 0 || sv->diem > 10) {
            printf("  -> Diem phai nam trong khoang 0 - 10!\n");
            return 0;
        }

        return 1;
    }

    return 0;
}

/* Kiem tra diem: chi nhan chu so va toi da mot dau cham */
int kiemTraDiem(char chuoi[], double *diem) {
    int i = 0;
    int coSo = 0;
    int coDauCham = 0;
    char *ketThuc = NULL;

    if (chuoi[0] == '\0')
        return 0;

    for (i = 0; chuoi[i] != '\0'; i++) {
        if (isdigit((unsigned char)chuoi[i])) {
            coSo = 1;
        } else if (chuoi[i] == '.' && !coDauCham) {
            coDauCham = 1;
        } else {
            return 0;
        }
    }

    if (!coSo)
        return 0;

    *diem = strtod(chuoi, &ketThuc);

    if (ketThuc == chuoi || *ketThuc != '\0')
        return 0;

    if (*diem < 0 || *diem > 10)
        return 0;

    return 1;
}

/* Kiem tra danh sach da co diem mon hay chua */
int coDiem(SinhVien ds[], int n) {
    int i = 0;

    for (i = 0; i < n; i++) {
        if (ds[i].tenMon[0] != '\0')
            return 1;
    }

    return 0;
}

/* Nhap MSSV va ho ten cho sinh vien */
void nhapSinhVien(SinhVien ds[], int *n, int *soSV) {
    char buf[200] = "";
    SinhVien sv = {0};
    int soLuong = 0;
    int i = 0;

    if (*soSV >= MAX_SINH_VIEN) {
        printf("\nDanh sach sinh vien da day!\n");
        return;
    }

    while (1) {
        nhapSoNguyen("Nhap so sinh vien can nhap: ",
                     1, MAX_SINH_VIEN, &soLuong);

        if (*soSV + soLuong > MAX_SINH_VIEN) {
            printf("  -> Chi co the nhap them toi da %d sinh vien!\n",
                   MAX_SINH_VIEN - *soSV);
            continue;
        }

        break;
    }

    for (i = 0; i < soLuong; i++) {
        memset(&sv, 0, sizeof(sv));

        printf("\n========== SINH VIEN %d ==========\n", *soSV + 1);

        while (1) {
            printf("Nhap MSSV (dung 8 chu so): ");
            docDong(buf, sizeof(buf));

            if (strlen(buf) != MAX_MSSV) {
                printf("  -> MSSV phai co dung 8 chu so!\n");
                continue;
            }

            strcpy(sv.maSV, buf);

            if (kiemTraLogic(ds, *n, &sv, 1))
                break;
        }

        while (1) {
            printf("Nhap ho ten: ");
            docDong(buf, sizeof(buf));
            xoaTrang(buf);

            if (strlen(buf) >= MAX_TEN) {
                printf("  -> Ho ten qua dai!\n");
                continue;
            }

            strcpy(sv.hoTen, buf);

            if (kiemTraLogic(ds, *n, &sv, 2))
                break;
        }

        sv.tenMon[0] = '\0';
        sv.diem = -1.0;

        ds[*n] = sv;
        (*n)++;
        (*soSV)++;

        printf("-> Da them sinh vien thanh cong!\n");
    }

    printf("\nDa nhap %d sinh vien. Tong so sinh vien: %d\n",
           soLuong, *soSV);
}

/* Nhap ten mon va diem theo MSSV */
void nhapDiem(SinhVien ds[], int *n) {
    char buf[200] = "";
    char maSV[MAX_MSSV + 1] = "";
    double diem = 0.0;
    int viTri = -1;
    int soMon = 0;
    int j = 0;
    int i = 0;
    int timThay = 0;
    int conCho = 0;

    while (1) {
        printf("\n========================================\n");
        printf("        NHAP DIEM SINH VIEN\n");
        printf("========================================\n");

        while (1) {
            printf("Nhap MSSV can them diem (0 de quay lai): ");
            docDong(buf, sizeof(buf));

            if (strcmp(buf, "0") == 0)
                return;

            if (strlen(buf) != MAX_MSSV) {
                printf("  -> MSSV phai co dung 8 chu so!\n");
                continue;
            }

            timThay = 1;

            for (i = 0; i < MAX_MSSV; i++) {
                if (!isdigit((unsigned char)buf[i])) {
                    timThay = 0;
                    break;
                }
            }

            if (!timThay) {
                printf("  -> MSSV chi duoc chua chu so!\n");
                continue;
            }

            strcpy(maSV, buf);
            timThay = 0;

            for (i = 0; i < *n; i++) {
                if (strcmp(ds[i].maSV, maSV) == 0) {
                    timThay = 1;
                    break;
                }
            }

            if (!timThay) {
                printf("  -> Khong tim thay MSSV nay!\n");
                continue;
            }

            break;
        }

        viTri = -1;

        for (i = 0; i < *n; i++) {
            if (strcmp(ds[i].maSV, maSV) == 0) {
                viTri = i;
                break;
            }
        }

        if (viTri < 0) {
            printf("  -> Khong tim thay ban ghi sinh vien!\n");
            continue;
        }

        printf("\nSinh vien: %s - %s\n",
               ds[viTri].maSV, ds[viTri].hoTen);

        while (1) {
            nhapSoNguyen("Nhap so mon can them: ",
                         1, MAX_SINH_VIEN, &soMon);

            conCho = MAX_SINH_VIEN - *n;

            if (ds[viTri].tenMon[0] == '\0')
                conCho++;

            if (soMon > conCho) {
                printf("  -> Danh sach chi con cho them toi da %d mon!\n",
                       conCho);
                continue;
            }

            break;
        }

        for (j = 0; j < soMon; j++) {
            SinhVien sv = {0};

            strcpy(sv.maSV, ds[viTri].maSV);
            strcpy(sv.hoTen, ds[viTri].hoTen);

            while (1) {
                printf("\nMon %d\n", j + 1);
                printf("Nhap ten mon: ");
                docDong(buf, sizeof(buf));
                xoaTrang(buf);

                if (strlen(buf) >= MAX_TEN_MON) {
                    printf("  -> Ten mon qua dai!\n");
                    continue;
                }

                strcpy(sv.tenMon, buf);

                if (kiemTraLogic(ds, *n, &sv, 3))
                    break;
            }

            while (1) {
                printf("Nhap diem (0 - 10): ");
                docDong(buf, sizeof(buf));

                if (!kiemTraDiem(buf, &diem)) {
                    printf("  -> Diem phai la so tu 0 den 10, "
                           "khong de trong, khong co khoang trang, "
                           "chu hoac ky tu khac!\n");
                    continue;
                }

                sv.diem = diem;
                break;
            }

            if (ds[viTri].tenMon[0] == '\0') {
                ds[viTri] = sv;
            } else {
                if (*n >= MAX_SINH_VIEN) {
                    printf("  -> Danh sach da day, khong the them mon!\n");
                    break;
                }

                ds[*n] = sv;
                (*n)++;
            }

            printf("-> Da them diem mon %s!\n", sv.tenMon);
        }

        printf("\nDa nhap diem cho MSSV %s xong.\n", maSV);
    }
}

/* Tao danh sach diem trung binh theo tung MSSV */
int taoDanhSachTB(SinhVien ds[], int n, SinhVienTB dsTB[]) {
    int soSV = 0;
    int i = 0;
    int j = 0;
    int daCo = 0;
    int soMon = 0;
    double tong = 0.0;

    for (i = 0; i < n; i++) {
        if (ds[i].tenMon[0] == '\0')
            continue;

        daCo = 0;

        for (j = 0; j < soSV; j++) {
            if (strcmp(dsTB[j].maSV, ds[i].maSV) == 0) {
                daCo = 1;
                break;
            }
        }

        if (daCo)
            continue;

        strcpy(dsTB[soSV].maSV, ds[i].maSV);
        strcpy(dsTB[soSV].hoTen, ds[i].hoTen);

        tong = 0.0;
        soMon = 0;

        for (j = 0; j < n; j++) {
            if (ds[j].tenMon[0] != '\0' &&
                strcmp(ds[j].maSV, ds[i].maSV) == 0) {
                tong += ds[j].diem;
                soMon++;
            }
        }

        dsTB[soSV].diemTB = soMon > 0 ? tong / soMon : 0.0;

        if (dsTB[soSV].diemTB < 5.0)
            strcpy(dsTB[soSV].xepLoai, "Yeu");
        else if (dsTB[soSV].diemTB < 6.5)
            strcpy(dsTB[soSV].xepLoai, "Kha");
        else if (dsTB[soSV].diemTB < 8.0)
            strcpy(dsTB[soSV].xepLoai, "Tot");
        else
            strcpy(dsTB[soSV].xepLoai, "Gioi");

        soSV++;
    }

    return soSV;
}

/* In danh sach chi tiet hoac bang diem trung binh */
void inBang(SinhVien ds[], int n, SinhVienTB dsTB[],
            int soSV, int loaiBang) {
    int i = 0;
    int stt = 0;

    if (loaiBang == 1) {
        printf("\n%-5s %-12s %-25s %-25s %-8s\n",
               "STT", "MSSV", "Ho ten", "Ten mon", "Diem");
        printf("-------------------------------------------------------------------------------\n");

        for (i = 0; i < n; i++) {
            if (ds[i].tenMon[0] == '\0')
                continue;

            stt++;

            printf("%-5d %-12s %-25s %-25s %-8.2lf\n",
                   stt, ds[i].maSV, ds[i].hoTen,
                   ds[i].tenMon, ds[i].diem);
        }
    } else if (loaiBang == 2) {
        printf("\n%-5s %-12s %-25s %-12s %-10s\n",
               "STT", "MSSV", "Ho ten", "Diem TB", "Xep loai");
        printf("-----------------------------------------------------------------\n");

        for (i = 0; i < soSV; i++) {
            printf("%-5d %-12s %-25s %-12.2lf %-10s\n",
                   i + 1, dsTB[i].maSV, dsTB[i].hoTen,
                   dsTB[i].diemTB, dsTB[i].xepLoai);
        }
    }
}

/* Sap xep theo MSSV hoac diem trung binh */
void sapXep(SinhVienTB dsTB[], int n) {
    SinhVienTB temp = {0};
    int chon = 0;
    int i = 0;
    int j = 0;
    int doiCho = 0;

    printf("\n========== SAP XEP ==========\n");
    printf("1. MSSV tang dan\n");
    printf("2. MSSV giam dan\n");
    printf("3. Diem trung binh tang dan\n");
    printf("4. Diem trung binh giam dan\n");
    printf("0. Quay lai\n");

    nhapSoNguyen("Lua chon: ", 0, 4, &chon);

    if (chon == 0)
        return;

    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            doiCho = 0;

            if (chon == 1 && strcmp(dsTB[i].maSV, dsTB[j].maSV) > 0)
                doiCho = 1;
            else if (chon == 2 &&
                     strcmp(dsTB[i].maSV, dsTB[j].maSV) < 0)
                doiCho = 1;
            else if (chon == 3 && dsTB[i].diemTB > dsTB[j].diemTB)
                doiCho = 1;
            else if (chon == 4 && dsTB[i].diemTB < dsTB[j].diemTB)
                doiCho = 1;

            if (doiCho) {
                temp = dsTB[i];
                dsTB[i] = dsTB[j];
                dsTB[j] = temp;
            }
        }
    }

    printf("\nDa sap xep xong!\n");
    inBang(NULL, 0, dsTB, n, 2);

    /* Hien thi xong thi nhap 0 de quay ve menu */
    choNhap0();
}

/* Tim sinh vien theo MSSV */
void timSinhVien(SinhVien ds[], int n) {
    char maSV[MAX_MSSV + 1] = "";
    int i = 0;
    int timThay = 0;
    int stt = 0;

    printf("\n========== TIM SINH VIEN ==========\n");

    while (1) {
        printf("Nhap MSSV can tim (0 de quay lai): ");
        docDong(maSV, sizeof(maSV));

        if (strcmp(maSV, "0") == 0)
            return;

        if (strlen(maSV) != MAX_MSSV) {
            printf("  -> MSSV phai co dung 8 chu so!\n");
            continue;
        }

        timThay = 1;

        for (i = 0; i < MAX_MSSV; i++) {
            if (!isdigit((unsigned char)maSV[i])) {
                timThay = 0;
                break;
            }
        }

        if (!timThay) {
            printf("  -> MSSV chi duoc chua chu so!\n");
            continue;
        }

        break;
    }

    timThay = 0;

    printf("\n%-5s %-12s %-25s %-25s %-8s\n",
           "STT", "MSSV", "Ho ten", "Ten mon", "Diem");
    printf("-------------------------------------------------------------------------------\n");

    for (i = 0; i < n; i++) {
        if (ds[i].tenMon[0] == '\0')
            continue;

        if (strcmp(ds[i].maSV, maSV) == 0) {
            stt++;

            printf("%-5d %-12s %-25s %-25s %-8.2lf\n",
                   stt, ds[i].maSV, ds[i].hoTen,
                   ds[i].tenMon, ds[i].diem);

            timThay = 1;
        }
    }

    if (!timThay)
        printf("Khong tim thay sinh vien co MSSV %s!\n", maSV);

    /* Hien thi ket qua tim kiem xong thi nhap 0 */
    choNhap0();
}

/* Loc sinh vien theo xep loai */
void locSinhVien(SinhVienTB dsTB[], int n) {
    int chon = 0;
    int i = 0;
    int timThay = 0;
    int stt = 0;
    const char *loai = "";

    printf("\n========== LOC SINH VIEN ==========\n");
    printf("1. Yeu\n");
    printf("2. Kha\n");
    printf("3. Tot\n");
    printf("4. Gioi\n");

    nhapSoNguyen("Lua chon: ", 1, 4, &chon);

    if (chon == 1)
        loai = "Yeu";
    else if (chon == 2)
        loai = "Kha";
    else if (chon == 3)
        loai = "Tot";
    else
        loai = "Gioi";

    printf("\n%-5s %-12s %-25s %-12s %-10s\n",
           "STT", "MSSV", "Ho ten", "Diem TB", "Xep loai");
    printf("-----------------------------------------------------------------\n");

    for (i = 0; i < n; i++) {
        if (strcmp(dsTB[i].xepLoai, loai) == 0) {
            stt++;

            printf("%-5d %-12s %-25s %-12.2lf %-10s\n",
                   stt, dsTB[i].maSV, dsTB[i].hoTen,
                   dsTB[i].diemTB, dsTB[i].xepLoai);

            timThay = 1;
        }
    }

    if (!timThay)
        printf("Khong co sinh vien nao thuoc loai nay!\n");

    /* Hien thi ket qua loc xong thi nhap 0 */
    choNhap0();
}

/* Xuat bang diem trung binh ra file */
void xuatFile(SinhVienTB dsTB[], int n) {
    FILE *f = NULL;
    int i = 0;

    f = fopen("bang_diem_trung_binh.txt", "w");

    if (f == NULL) {
        printf("Khong the mo file!\n");
        return;
    }

    fprintf(f, "%-5s %-12s %-25s %-12s %-10s\n",
            "STT", "MSSV", "Ho ten", "Diem TB", "Xep loai");
    fprintf(f, "-----------------------------------------------------------------\n");

    for (i = 0; i < n; i++) {
        fprintf(f, "%-5d %-12s %-25s %-12.2lf %-10s\n",
                i + 1, dsTB[i].maSV, dsTB[i].hoTen,
                dsTB[i].diemTB, dsTB[i].xepLoai);
    }

    fclose(f);

    printf("\nDa xuat file thanh cong!\n");
    printf("Ten file: bang_diem_trung_binh.txt\n");
}
