#include <iostream>
#include <string>
using namespace std;

class CanBo
{
protected:
    int MaCanBo;
    string HoTen;
    string NgaySinh;
    long Luong;

public:
    virtual void Nhap()
    {
        cout << "Nhap ma can bo: ";
        cin >> MaCanBo;
        cout << "Nhap ho ten: ";
        cin.ignore();
        getline(cin, HoTen);
        cout << "Nhap ngay sinh: ";
        getline(cin, NgaySinh);
    }
    virtual void Xuat()
    {
        cout << "Ma can bo: " << MaCanBo << endl;
        cout << "Ho ten: " << HoTen << endl;
        cout << "Ngay sinh: " << NgaySinh << endl;
    }
    virtual long TinhLuong() = 0;
    virtual bool getLoai() = 0;
};

class CanBoThuocBienCheNhaNuoc : public CanBo
{
protected:
    long LuongCoBan;
    float HeSoLuong;
    float HeSoPhuCap;

public:
    void Nhap()
    {
        CanBo::Nhap();
        cout << "Nhap luong co ban: ";
        cin >> LuongCoBan;
        cout << "Nhap he so luong: ";
        cin >> HeSoLuong;
        cout << "Nhap he so phu cap: ";
        cin >> HeSoPhuCap;
    }
    void Xuat()
    {
        CanBo::Xuat();
        cout << "Luong co ban: " << LuongCoBan << endl;
        cout << "He so luong: " << HeSoLuong << endl;
        cout << "He so phu cap: " << HeSoPhuCap << endl;
    }
    long TinhLuong()
    {
        long BaoHiem = LuongCoBan * HeSoLuong * 0.115;
        long LuongThueTruoc = LuongCoBan * HeSoLuong * HeSoPhuCap - BaoHiem;
        long ThueThuNhapCaNhan = 0;
        if (LuongThueTruoc > 11000000)
        {
            long LuongVuot = LuongThueTruoc - 11000000;
            if (LuongVuot <= 10000000)
            {
                ThueThuNhapCaNhan = LuongVuot * 0.05;
            }
            else if (LuongVuot <= 22000000)
            {
                ThueThuNhapCaNhan = 500000 + (LuongVuot - 10000000) * 0.1;
            }
            else
            {
                ThueThuNhapCaNhan = 500000 + 1200000 + (LuongVuot - 22000000) * 0.15;
            }
        }
        Luong = LuongThueTruoc - ThueThuNhapCaNhan;
        return Luong;
    }
    bool getLoai()
    {
        return true;
    }
};

class CanBoHopDong : public CanBo
{
protected:
    long TienCongNgay;
    int SoNgayCong;
    float HeSoVuotGio;

public:
    void Nhap()
    {
        CanBo::Nhap();
        cout << "Nhap tien cong ngay: ";
        cin >> TienCongNgay;
        cout << "Nhap so ngay cong: ";
        cin >> SoNgayCong;
        cout << "Nhap he so vuot gio: ";
        cin >> HeSoVuotGio;
    }
    void Xuat()
    {
        CanBo::Xuat();
        cout << "Tien cong ngay: " << TienCongNgay << endl;
        cout << "So ngay cong: " << SoNgayCong << endl;
        cout << "He so vuot gio: " << HeSoVuotGio << endl;
    }
    long TinhLuong()
    {
        long LuongTruocThue = TienCongNgay * SoNgayCong * HeSoVuotGio;
        long ThueTamUng = LuongTruocThue * 0.1;
        Luong = LuongTruocThue - ThueTamUng;
        return Luong;
    }
    bool getLoai()
    {
        return false;
    }
};

class CongTy
{
protected:
    CanBo **a;
    int n;

public:
    void Nhap()
    {
        cout << "Nhap so luong can bo: ";
        cin >> n;
        a = new CanBo *[n];
        for (int i = 0; i < n; i++)
        {
            int chon;
            cout << "Nhap 1 de nhap can bo bien che, 2 de nhap can bo hop dong: ";
            cin >> chon;
            if (chon == 1)
            {
                a[i] = new CanBoThuocBienCheNhaNuoc;
            }
            else
            {
                a[i] = new CanBoHopDong;
            }
            a[i]->Nhap();
        }
    }
    void Xuat()
    {
        for (int i = 0; i < n; i++)
        {
            a[i]->Xuat();
            cout << "Luong: " << a[i]->TinhLuong() << endl;
        }
    }
    long TongLuong()
    {
        long Tong = 0;
        for (int i = 0; i < n; i++)
        {
            Tong += a[i]->TinhLuong();
        }
        return Tong;
    }
    void LuongThapNhat()
    {
        cout << "Danh sach can bo bien che co luong thap nhat:" << endl;
        long min = 0;
        for (int i = 0; i < n; i++)
        {
            if (a[i]->getLoai() == true)
            {
                min = a[i]->TinhLuong();
                break;
            }
        }
        for (int i = 0; i < n; i++)
        {
            if (a[i]->getLoai() == true && a[i]->TinhLuong() < min)
            {
                min = a[i]->TinhLuong();
            }
        }
        for (int i = 0; i < n; i++)
        {
            if (a[i]->getLoai() == true && a[i]->TinhLuong() == min)
            {
                a[i]->Xuat();
                cout << "Luong: " << a[i]->TinhLuong() << endl;
            }
        }
    }
};

int main()
{
    CongTy a;
    a.Nhap();
    cout << "Thong tin danh sach can bo: " << endl;
    a.Xuat();
    cout << "Tong luong: " << a.TongLuong() << endl;
    a.LuongThapNhat();
    return 0;
}