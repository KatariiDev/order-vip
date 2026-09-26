#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char maSV[20];
    char hoTen[100];
    double diemToan;
    double diemLy;
    double diemHoa;
    double diemTB;
    char xepLoai[20];
	} SinhVien;

void xoaBND () {
	int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

double nhapDiem(const char tenMon[]) {
    double diem;
    int ketQua;
    while (1) {
        printf("Nhap diem %s: ", tenMon);
        ketQua = scanf("%lf", &diem);
if (ketQua != 1) {
            printf("Vui long nhap diem bang so!\n");
            xoaBND();
        } else if (diem < 0 || diem > 10) {
            printf("Diem phai tu 0 den 10!\n");
        } else {
            xoaBND(); //
            return diem;
        }
    }
}

void inThongTin(SinhVien sv) {
    printf("\n===== THONG TIN SINH VIEN =====\n");
    printf("Ma sinh vien: %s\n", sv.maSV);
    printf("Ho ten: %s\n", sv.hoTen);
    printf("Diem Toan: %.2f\n", sv.diemToan);
    printf("Diem Ly: %.2f\n", sv.diemLy);
    printf("Diem Hoa: %.2f\n", sv.diemHoa);
    printf("Diem trung binh: %.2f\n", sv.diemTB);
    printf("Xep loai: %s\n", sv.xepLoai); 
}

int main() {
    SinhVien sv;
    int luaChon;
    int daNhapThongTin = 0;

    do {
        printf("\n======= MENU =======\n");
        printf("1. Nhap thong tin va diem sinh vien\n");
        printf("2. In thong tin sinh vien\n");
        printf("0. Thoat\n");
        printf("====================\n");
        printf("Chon chuc nang: ");
        
        if (scanf("%d", &luaChon) != 1) {
            printf("Vui long nhap so!\n");
            xoaBND();
            continue;
        }
        switch (luaChon) {
            case 1:
                printf("\n--- NHAP THONG TIN ---\n");
                printf("Nhap ma sinh vien: ");
                scanf("%19s", sv.maSV);
                xoaBND(); 

                printf("Nhap ho ten: ");
                fgets(sv.hoTen, sizeof(sv.hoTen), stdin);
                sv.hoTen[strcspn(sv.hoTen, "\n")] = 0;

                sv.diemToan = nhapDiem("Toan");
                sv.diemLy = nhapDiem("Ly");
                sv.diemHoa = nhapDiem("Hoa");

//                sv.diemTB = tinhDiemTB(sv.diemToan, sv.diemLy, sv.diemHoa);
//                xepLoai(sv.diemTB, sv.xepLoai);
                
                daNhapThongTin = 1;
                printf("-> Nhap thong tin thanh cong!\n");
                break;
            
            case 2:
                if (!daNhapThongTin) {
                    printf("Vui long nhap thong tin sinh vien (Chon 1) truoc!\n");
                } else {
                    inThongTin(sv);
                }
                break;
            
            case 0:
                printf("Thoat chuong trinh.\n");
                break;
            
            default:
                printf("Lua chon khong hop le, vui long thu lai!\n");
                break;
        }
    } while (luaChon != 0);

    return 0;
}
 
