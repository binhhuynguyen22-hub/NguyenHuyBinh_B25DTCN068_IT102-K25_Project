#include<stdio.h>
#include<math.h>
#include<limits.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#define MAX 100
typedef struct Room{
    char roomId[5];
    int type;
    double price;
    int status;

    char cusName[50];
    char checkInDate[11];
    int days;
} Room;
typedef struct Booking{
    char bookId[20];
    char roomId[5];
    char customerName[50];
    char checkInDate[11];
    int days;
    double totalCost;
} Booking;

void addRoom(Room listroom[], int *n);
void value(Room listroom[], int *n);
void pauseScreen();
void updateRoom(Room listroom[], int n);
void maintenanceRoom(Room listroom[],int n);
void displayRoom(Room listroom[],int n);
void searchRoomByType(Room listroom[],int n);
void sortRoomByPrice(Room listroom[],int n);
void checkIn(Room listroom[], int n, Booking bookings[], int *bookingCount);
void RoomRentalHistory(Booking bookings[], int bookingCount);
int isValidateInteger(char *str);
int readIntegertype(const char *promt,int min, int max);
int isValidDate(char *date);
int readIntegerStatus(const char *promt,int min, int max);
int readIntegerOption(const char *promt,int min, int max);
int isValidateDouble(char *str);
double readDoublePrice(const char *promt,double min);
int stringToInt(char *str, int start, int length);
int main()
{
    int op;
    Room listroom[MAX];
    int Count = 0;
    Booking bookings[MAX];  
    int bookingCount = 0;
    value(listroom, &Count);
    
    do{
        printf("----------------------------------------------\n");
        printf("|               QUAN LI KHACH SAN            |\n");
        printf("----------------------------------------------\n");
        printf("|1. Them phong moi                           |\n");
        printf("|2. Cap nhat phong                           |\n");
        printf("|3. Bao tri phong(khoa)                      |\n");
        printf("|4. Hien thi danh sach                       |\n");
        printf("|5. Tim kiem                                 |\n");
        printf("|6. Sap xep danh sach phong(theo gia)        |\n");
        printf("|7. Check-in(giao dich)                      |\n");
        printf("|8. Lich su thue                             |\n");
        printf("|9. Thoat                                    |\n");
    	printf("|--------------------------------------------|\n");
        
        op=readIntegerOption("Moi ban nhap lua chon: ",1,9);
    	system("cls");
        switch(op){
            case 1: addRoom(listroom, &Count);
            	pauseScreen();
				break;
            case 2: updateRoom(listroom, Count); 
            	pauseScreen();
				break;
            case 3: maintenanceRoom(listroom,Count);
				break;
            case 4: displayRoom(listroom,Count);
				break;
            case 5: searchRoomByType(listroom,Count);
				break;
            case 6: sortRoomByPrice(listroom, Count);
    			pauseScreen();
				break;
            case 7: checkIn(listroom, Count, bookings, &bookingCount);
				break;
            case 8: RoomRentalHistory(bookings, bookingCount);
				break;
            case 9:
                printf("cam on da su dung, hen gap lai ban!!!");
                exit(0);
                break;
            default:
                printf("Lua chon khong hop le!\n");
        }
    } while(op != 9);
}
void pauseScreen(){
	printf("nhap enter de tiep tuc...");
	getchar();
}
void value(Room listroom[], int *n){
    Room Data[7] = {
        {"101", 1, 150000, 0},
        {"102", 2, 500000, 0},
        {"103", 1, 280000, 0},
        {"104", 2, 550000, 0},
        {"105", 1, 320000, 0},
        {"106", 2, 600000, 0},
        {"107", 1, 290000, 0}
    };

    *n = 7;
    for(int i = 0; i < *n; i++){
        listroom[i] = Data[i];
    }
}
int isValidateDouble(char *str){
    if(strlen(str) == 0) return 0;

    int dot = 0;
    int start = 0;

    if(str[0] == '-' || str[0] == '+')
        start = 1;

    if(strlen(str) == start) return 0;

    for(int i = start; i < strlen(str); i++){
        if(str[i] == '.'){
            dot++;
            if(dot > 1) return 0;
        } 
        else if(!isdigit(str[i])){
            return 0;
        }
    }
    return 1;
}
double readDoublePrice(const char *promt, double min){
    char buffer[50];
    double number;
    int isvalidate;

    do{
        isvalidate = 1;
        printf("%s", promt);
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0';

        if(strlen(buffer) == 0){
            printf("Khong duoc de trong!\n");
            isvalidate = 0;
            continue;
        }

        if(!isValidateDouble(buffer)){
            printf("Loi: chi duoc nhap so thuc!\n");
            isvalidate = 0;
            continue;
        }

        number = atof(buffer);

        if(number < min ){
            printf("gia tien phai lon hon khong\n");
            isvalidate = 0;
        }

    }while(!isvalidate);

    return number;
}
int isValidateInteger(char *str){
	if(strlen(str)==0){
		return 0;
	}
	int start=0;
	if(str[0]=='-'||str[0]=='+'){
		start=1;
	}
	if(strlen(str)==start){
		return 0;
	}
	for(int i= start;i<strlen(str);i++){
		if(!isdigit(str[i])){
			return 0;
		}
	}
	return 1;
}
int readIntegertype(const char *promt,int min, int max){
    char buffer[50];
    int number;
	int isvalidate;
    do{
    	isvalidate=1;
    	printf("%s",promt);
    	fgets(buffer,sizeof(buffer),stdin);
    	buffer[strcspn(buffer, "\n")] = '\0';
    	
		if(strcmp(buffer," ")==0||strlen(buffer)==0){
			printf("ko dc de trong thong tin!\n");
			isvalidate=0;
			continue;
		}
        if(!isValidateInteger(buffer)){
            printf("Loi: chi duoc nhap vao so!\n");
            isvalidate=0;
            continue;
        }

        number = atoi(buffer);
        if(number<min||number>max){
        	printf("chi dc nhap %d hoac %d\n",min,max);
        	isvalidate=0;
        	continue;
		}
    }while(!isvalidate);

    return number;
}
int readIntegerStatus(const char *promt,int min, int max){
    char buffer[50];
    int number;
	int isvalidate;
    do{
    	isvalidate=1;
    	printf("%s",promt);
    	fgets(buffer,sizeof(buffer),stdin);
    	buffer[strcspn(buffer, "\n")] = '\0';
    	
		if(strcmp(buffer," ")==0||strlen(buffer)==0){
			printf("ko dc de trong thong tin!\n");
			isvalidate=0;
			continue;
		}
        if(!isValidateInteger(buffer)){
            printf("Loi: chi duoc nhap vao so!\n");
            isvalidate=0;
            continue;
        }

        number = atoi(buffer);
        if(number<min||number>max){
        	printf("chi dc nhap tu %d den %d\n",min,max);
        	isvalidate=0;
        	continue;
		}
    }while(!isvalidate);

    return number;
}
int stringToInt(char *str, int start, int length) {
    int result = 0;
    for (int i = start; i < start + length; i++) {
        if (str[i] < '0' || str[i] > '9') return -1;
        result = result * 10 + (str[i] - '0');
    }
    return result;
}
int isValidDate(char *date) {
    if (strlen(date) != 10) return 0;
    if (date[2] != '/' || date[5] != '/') {
    	return 0;
	}

    for (int i = 0; i < 10; i++) {
        if (i == 2 || i == 5) 
		continue;
        if (date[i] < '0' || date[i] > '9') {
        	return 0;
		}
		
    }

    int day = stringToInt(date, 0, 2);
    int month = stringToInt(date, 3, 2);
    int year = stringToInt(date, 6, 4);

    if (day < 1 || day > 31) {
    return 0;	
	}
	
    if (month < 1 || month > 12) {
    return 0;
	}

    if (year < 1900 || year > 2100) {
    return 0;	
	}


    int daysInMonth[] = {0,31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        daysInMonth[1] = 29;
    }

    if (day > daysInMonth[month - 1]){
    	return 0;
	} 

    return 1;
}

int readIntegerOption(const char *promt,int min, int max){
    char buffer[50];
    int number;
    int isvalidate;
    do{
        isvalidate=1;
        printf("%s",promt);
        fgets(buffer,sizeof(buffer),stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        
        if(strcmp(buffer," ")==0||strlen(buffer)==0){
            printf("ko dc de trong thong tin!\n");
            isvalidate=0;
            continue;
        }
        if(!isValidateInteger(buffer)){
            printf("Loi: chi duoc nhap vao so!\n");
            isvalidate=0;
            continue;
        }

        number = atoi(buffer);
        if(number<min||number>max){
            printf("chi dc nhap tu %d den %d\n",min,max);
            isvalidate=0;
            continue;
        }
    }while(!isvalidate);

    return number;
}
void addRoom(Room listroom[], int *n) {
	int i=*n;
    printf("\nTHEM PHONG MOI\n");

    int exists;// flag
    do {
        exists = 0;
        printf("Nhap ma phong: ");
        fgets(listroom[i].roomId, sizeof(listroom[i].roomId), stdin);
        listroom[i].roomId[strcspn(listroom[i].roomId, "\n")] = '\0';
        
        if(strlen(listroom[i].roomId) == 0) {
            printf("Loi: Ma phong khong duoc rong!\n");
            continue;
        }

        for(int j = 0; j < *n; j++) {
            if(strcmp(listroom[j].roomId, listroom[i].roomId) == 0) {
                exists = 1;
                break;
            }
        }

        if(exists)
            printf("Loi: Phong %s da ton tai!\n", listroom[i].roomId);

    } while(strlen(listroom[i].roomId) == 0 || exists);
		listroom[i].type=readIntegertype("moi ban nhap vao loai phong(1: Don, 2:Doi): ",1,2);

//    do {
//        printf("Nhap gia phong moi dem: ");
//        scanf("%lf", &listroom[i].price); 
//		getchar();
//        if(listroom[i].price <= 0)
//            printf("Loi: Gia phong phai lon hon 0!\n");
//    } while(listroom[i].price <= 0);
		listroom[i].price=readDoublePrice("Moi ban nhap vao gia: ",0.01);

    listroom[i].status = 0;

    listroom[*n] = listroom[i];
    (*n)++;

    printf("Them phong %s thanh cong! phong da duoc tao voi trang thai trong\n", listroom[i].roomId);
}
void updateRoom(Room listroom[], int n) {
    char id[5];
    printf("\nCAP NHAT PHONG\n");
    printf("Nhap ma phong: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = '\0';

    for(int i = 0; i < n; i++){
        if(strcmp(listroom[i].roomId, id) == 0){

            if(listroom[i].status == 1) {
                printf("Phong dang co khach, khong the cap nhat!\n");
                pauseScreen();
                return;
            }

            printf("Phong: %s | Loai: ", listroom[i].roomId);

            if (listroom[i].type == 1) {
                printf("Don");
            } else {
                printf("Doi");
            }

            printf(" | Gia: %.2lf | Status: %d\n", listroom[i].price, listroom[i].status);
            pauseScreen();
            
            listroom[i].type = readIntegertype("Moi ban nhap vao loai phong(1: Don, 2:Doi): ", 1, 2);
            listroom[i].price = readDoublePrice("Moi ban nhap vao gia: ", 0.01);
            listroom[i].status = readIntegerStatus("Nhap vao trang thai phong moi: ", 0, 2);

            printf("Cap nhat thong tin phong %s thanh cong!\n", listroom[i].roomId);
            return;
        }
    }

    printf("Khong tim thay phong [%s]!\n", id);
}
void maintenanceRoom(Room listroom[],int n){
	if(n==0){
		printf("hien tai khong co phong!\n");
		return;
	}
	char roomId[5];
	int found=0;
	
	do{
		printf("Nhap so phong can bao tri: ");
		fgets(roomId,sizeof(roomId),stdin);
		roomId[strcspn(roomId,"\n")]='\0';
		
		for(int i=0;i<n;i++){
			if(strcmp(listroom[i].roomId,roomId)==0){
				found=1;
				if(listroom[i].status==1){
					printf("Phong dang co nguoi thue khong the bao tri\n");
				}else{
					listroom[i].status=2;
					printf("phong da duoc bao tri\n");
				}
				break;
			}
		}
		if(!found){
			printf("phong khong ton tai\n");
		}
	}while(!found);
}
void displayRoom(Room listroom[], int n){
    if(n == 0){
        printf("Khong co phong trong danh sach de hien thi\n");
        return;
    }
    
    int itemsPerPage = 2;
    int totalPage = (n + itemsPerPage - 1) / itemsPerPage;
    int page = 0;
    
    while(1){
        system("cls");
        printf("Trang %d/%d\n", page + 1, totalPage);
        
        for(int i = 0; i < 70; i++) printf("=");
        printf("\n|%-6s|%-30s|%-20s|%-10s|\n", "roomId", "typeRoom", "price", "status");
        for(int i = 0; i < 70; i++) printf("-");
        printf("\n");
        
        int start = page * itemsPerPage;
        int end = start + itemsPerPage;
        if(end > n) end = n;
        
        for(int i = start; i < end; i++){
            printf("|%-6s|", listroom[i].roomId);
            
            if(listroom[i].type == 1){
            	
            	printf("%-30s|", "Don");
			}
            else{
            	printf("%-30s|", "Doi");
			}
            printf("%-20.2lf|", listroom[i].price);
            
            if(listroom[i].status == 0){
            	printf("%-10s|\n", "Trong");
			}
                
            else if(listroom[i].status == 1){
            	 printf("%-10s|\n", "Dang thue");
			}
               
            else{
            	printf("%-10s|\n", "Bao tri");
			}
                
        }
        
        for(int i = 0; i < 70; i++) printf("-");
        printf("\n");
        
        printf("\nNhap so trang de chuyen (1-%d)", totalPage);
        printf("\nNhan Enter de sang trang tiep theo");
        printf("\nNhap q de thoat: ");
        
        char input[10];
        if(fgets(input, sizeof(input), stdin) == NULL){
            break;
        }
        
        input[strcspn(input, "\n")] = '\0';

		if(strlen(input) == 0){
    		if(page < totalPage - 1){
        	page++;
    	} else {
        printf("\nDa den trang cuoi! Nhan Enter de thoat...");
        getchar();
        break;
   			}
		}
		else if(strcmp(input, "q")==0||strcmp(input, "Q") == 0){
    		break;
		}
		else{
    	int choosePage = atoi(input);
    	if(choosePage >= 1 && choosePage <= totalPage){
        page = choosePage - 1;
    		}
    	else{
        printf("\nLua chon khong hop le! Nhan Enter de thu lai...");
        while(getchar() != '\n');
        getchar();
    		}
		}
	}
}
void searchRoomByType(Room listroom[], int n){
    if(n == 0){
        printf("Khong co phong de tim!\n");
        pauseScreen();
        return;
    }

    int type;
    do{
        printf("Nhap loai phong can tim (1: Don, 2: Doi): ");
        scanf("%d", &type);
        getchar();
    }while(type != 1 && type != 2);

    int found = 0;

    for(int i = 0; i < 70; i++){
    	
    	printf("=");
	} 
    printf("\n|%-6s|%-30s|%-20s|%-10s|\n","roomId","typeRoom","price","status");
    for(int i = 0; i < 70; i++){
    	
    	printf("-");
	}	
    printf("\n");

    for(int i = 0; i < n; i++){
        if(listroom[i].type == type){
            found = 1;

            printf("|%-6s|", listroom[i].roomId);

            if(listroom[i].type == 1)
                printf("%-30s|", "Don");
            else
                printf("%-30s|", "Doi");

            printf("%-20.2lf|", listroom[i].price);

            if(listroom[i].status == 0)
                printf("%-10s|\n", "Trong");
            else if(listroom[i].status == 1)
                printf("%-10s|\n", "Dang thue");
            else
                printf("%-10s|\n", "Bao tri");
        }
    }

    for(int i = 0; i < 70; i++) printf("-");
    printf("\n");

    if(!found){
        printf("Khong tim thay phong phu hop!\n");
    }

    pauseScreen();
}
void sortRoomByPrice(Room listroom[], int n){
    if(n == 0){
        printf("Khong co phong de sap xep!\n");
        return;
    }

    Room temp;
    for(int i = 0; i < n - 1; i++){
        for(int j = i + 1; j < n; j++){
            if(listroom[i].price < listroom[j].price){ // gi?m d?n
                temp = listroom[i];
                listroom[i] = listroom[j];
                listroom[j] = temp;
            }
        }
    }

    printf("Da sap xep danh sach phong theo gia giam dan!\n");

    for(int i = 0; i < 70; i++) printf("=");
    printf("\n|%-6s|%-30s|%-20s|%-10s|\n","roomId","typeRoom","price","status");
    for(int i = 0; i < 70; i++) printf("-");
    printf("\n");

    for(int i = 0; i < n; i++){
        printf("|%-6s|", listroom[i].roomId);
        if(listroom[i].type == 1){
        	printf("%-30s|", "Don");
		}
            
        else{
        	printf("%-30s|", "Doi");
		}
            

        printf("%-20.2lf|", listroom[i].price);

        if(listroom[i].status == 0){
        	printf("%-10s|\n", "Trong");
		}
            
        else if(listroom[i].status == 1){
        	printf("%-10s|\n", "Dang thue");
		}
            
        else{
        	 printf("%-10s|\n", "Bao tri");
		}
           
    }

    for(int i = 0; i < 70; i++) printf("-");
    printf("\n");
}

void checkIn(Room listroom[], int n, Booking bookings[], int *bookingCount) {
    if (n == 0) {
        printf("Chua co phong trong he thong!\n");
        pauseScreen();
        return;
    }

    char roomId[10];
    int found = -1;

    printf("CHECK-IN (Giao dich nhan phong)\n");
    printf("Nhap ma phong can check-in: ");
    fgets(roomId, sizeof(roomId), stdin);
    roomId[strcspn(roomId, "\n")] = '\0';

    for (int i = 0; i < n; i++) {
        if (strcmp(listroom[i].roomId, roomId) == 0) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("Loi: Khong tim thay phong!\n");
        pauseScreen();
        return;
    }

    if (listroom[found].status != 0) {
        if (listroom[found].status == 1) {
            printf("Loi: Phong da co khach!\n");
        } else if (listroom[found].status == 2) {
            printf("Loi: Phong dang bao tri!\n");
        }
        pauseScreen();
        return;
    }

    char cusName[50];
    printf("Nhap ten khach hang: ");
    fgets(cusName, sizeof(cusName), stdin);
    cusName[strcspn(cusName, "\n")] = '\0';

    int validDate = 0;
    char checkInDate[11];
    do {
        printf("Nhap ngay nhan phong (DD/MM/YYYY): ");
        fgets(checkInDate, sizeof(checkInDate), stdin);
        checkInDate[strcspn(checkInDate, "\n")] = '\0';
        int year = stringToInt(checkInDate, 6, 4); 
        if(year >= 2025 && isValidDate(checkInDate)) {
            validDate = 1;
        } else {
            printf("Loi: vui long nhap dung dinh dang!\n");
        }
        fflush(stdin);
    } while (!validDate);

    int days = readIntegerOption("Nhap so ngay thue (1-365): ", 1, 365);
    double totalCost = listroom[found].price * days;

    char bookId[20];
	strcpy(bookId, "MA");
	strcat(bookId, listroom[found].roomId);

	listroom[found].status = 1;
	strcpy(listroom[found].cusName, cusName);
	strcpy(listroom[found].checkInDate, checkInDate);
	listroom[found].days = days;

	strcpy(bookings[*bookingCount].checkInDate, checkInDate);
	strcpy(bookings[*bookingCount].bookId, bookId);
	strcpy(bookings[*bookingCount].roomId, listroom[found].roomId);
	strcpy(bookings[*bookingCount].customerName, cusName);
	bookings[*bookingCount].days = days;
	bookings[*bookingCount].totalCost = totalCost;
	(*bookingCount)++;

    printf("Check-in thanh cong, ma dat phong: %s\n", bookId);

    printf("\n===== HOA DON CHECK-IN =====\n");
    printf("Ma booking: %s\n", bookId);
    printf("Phong     : %s\n", listroom[found].roomId);
    printf("Khach     : %s\n", listroom[found].cusName);
    printf("Ngay nhan : %s\n", listroom[found].checkInDate);
    printf("So ngay   : %d\n", listroom[found].days);
    printf("Tong tien : %.2lf VND\n", totalCost);
    printf("===========================\n");
	system("cls");
    pauseScreen();
}

void RoomRentalHistory(Booking bookings[], int bookingCount) {
    if (bookingCount == 0) {
        printf("Chua co giao dich nao trong he thong!\n");
        return;
    }

    char roomId[10];
    printf("\nLICH SU THUE PHONG\n");
    printf("Nhap ma phong can xem lich su: ");
    fgets(roomId, sizeof(roomId), stdin);
    roomId[strcspn(roomId, "\n")] = '\0';

    int found = 0;
    for (int i = 0; i < bookingCount; i++) {
        if (strcmp(bookings[i].roomId, roomId) == 0) {
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Phong [%s] chua tung co khach thue!\n", roomId);
        return;
    }

    for (int i = 0; i < 91; i++) printf("=");
    printf("\n|%-5s|%-15s|%-10s|%-18s|%-15s|%-8s|%-12s|\n",
           "STT", "Booking ID", "So phong", "Ten khach","Ngay check in", "So ngay", "Tong tien");
    for (int i = 0; i < 91; i++) printf("-");
    printf("\n");

    int stt = 1;
    for (int i = 0; i < bookingCount; i++) {
        if (strcmp(bookings[i].roomId, roomId) == 0) {
            printf("|%-5d|%-15s|%-10s|%-18s|%-15s|%-8d|%-12.2lf|\n",stt,bookings[i].bookId,bookings[i].roomId,bookings[i].customerName,bookings[i].checkInDate,bookings[i].days,bookings[i].totalCost);
            stt++;
        }
    }

    for (int i = 0; i < 91; i++) printf("=");
    printf("\n");
}
