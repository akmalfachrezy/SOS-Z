#include <stdio.h>

void inis_papan ();
void besar_papan ();
void gambar_papan ();
int square_valid (int,int);
int cek_papan ();
int find_sos (int,int,int,char);
void two_player ();
void howtoplay ();
void player_move();
void winner();
int skor(int,int);

char board[10][10];
int Player1, Player2, n;

int main ()
{
	int mulai;
		printf("Selamat datang di game SOS\n"); //Pemilihan menu
		printf("1.PLAY GAME\n");
		printf("2.HOW TO PLAY\n");
		printf("3.EXIT\n");
		printf("\nMasukkan pilihan: ");
		scanf("%d",&mulai);
	if(mulai==1){
		besar_papan();
		inis_papan();
		two_player();
		if(cek_papan()){
			gambar_papan();
			winner();
		}  
	}	
	else if (mulai==2){
		howtoplay();
	}
	else if(mulai==3){
		system("cls");
		printf("\n\t\tBYE!!!\n");
	}
	return 0;
}
void besar_papan(){
	system("cls");
    printf("Besar papan adalah nxn, berapa besar n yang kamu inginkan? (3-10)\n");
    
    do{
   		scanf("%d", &n);
   		if(n<3){
   			printf("Papan tidak lebih kecil dari 3x3  : ");
		}
		if(n>10){
			printf("Papan tidak lebih besar dari 10x10: ");
		}
    }while((n<3) || (n>10));
	
}

void inis_papan()
{
	system("cls");
	int row,col;
	for (row = 0; row < n; row++)
	{
		for (col=0; col<n; col++)
		{
			board[row][col]=' ';
		}
	}
	Player1 = 0;
	Player2 = 0;
	
}

void gambar_papan()
{
	int row, col,ii;
	int angka1=1, angka2=1, angka3=3; //angka1=1 untuk menggambarkan angka penanda diatas papan
	printf("\n");					  //angka2=1 untuk menggambar angka penanda di setiap baris 
	printf("  ");					  //angka3=3 untuk jumlah spasi 
	for( ii=0; ii<((n*4)+1); ii++){ 
		if (ii==angka3){
			printf("%d", angka1); 
			angka1++;
			angka3 = angka3 + 4;
		}
		else{
			printf(" ");
		}
	}
	printf("\n");
	for (row=0; row<n; row++)
	{
		printf(" %d |",angka2);
		angka2++;
		for (col=0; col<n; col++)
		{
			printf(" %c |",board[row][col]); //write huruf yang diinput di kotak
		}
		printf(" \n");
		if (row != n)
		{
			printf("   ");
			for(ii=0; ii<((n*4)+1); ii++)
			{ 
				printf("-");
			}
			printf(" \n");
		}
	}
	printf("\n");		
		printf("Player1 %d : %d Player2\n", Player1, Player2);	

}

int cek_papan()//mengecek apakah kotak masih ada yang kosong
{
	int row, col;
	
	for (row=0; row<n; row++)
	{
		for(col=0; col<n; col++)
		{
			if (board[row][col] == ' ')
			{
				return 0;
			}
		}
	}
}

int square_valid (int row, int col)
{//pengecekan apakah kotak yang akan diisi kosong
 
	if (board[row][col]==' ')
	{
		return 1;
	}
	else 
	{
		return 0;
	} 

}

void two_player()
{
	do
	{
		player_move(1);
		if(cek_papan())
		{ 
			gambar_papan();
			winner();
		}
		player_move(2);
	}while (!cek_papan());//ulangi selama papan masih ada yang kosong
	
}

void player_move(int player)
{
  int x,y;
  int row, col;
  char symbol;
  do
  {
  	if(cek_papan()){//digunakan untuk mengecek kondisi ketika mendapatkan sos di kotak terakhir
  		return;
	  }
	gambar_papan(); 
        printf("\nPlayer %d, pilih baris dan kolom yang akan diisi contoh (1,2)  : ",player);
	
	do{
			scanf("%d,%d", &x,&y);		
			row = (x-1);// baris yan ingin di input
			col = (y-1);// kolom yan ingin di input
	
	}while(!square_valid(row,col));// ulangi selama kotak sudah terisi
	
	printf("Pilih huruf yang ingin dimasukkan di baris %d kolom %d (S or O) : ", x,y);
	do 
	{
		symbol = getchar();
	}while ((symbol != 'S') && (symbol != 's') && (symbol != 'O') && (symbol != 'o') && (symbol != '0')); 
	

	if((symbol == 'S') || (symbol == 's'))
	{
		symbol = 'S';
	}
	else 
	{
		symbol = 'O';	
	}

	board[row][col] = symbol; 
   }while(find_sos (row,col,player,symbol)); //ulangi selama menemukan sos, jika tidak kembali ke modul two_player
   
}
int find_sos (int row, int col,int player, char symbol)
{
	int sos;
	
	sos = 0; //digunakan untuk menampung skor
	
  if(symbol == 'S')
  {
	if ((board[row][col-2] == 'S') && (board[row][col-1] == 'O'))
	{
		sos++;//mengecek huruf s di kiri kotak ke2 dan huruf o dikiri kotak ke1(tengah) 
	}
	if ((board[row][col+1]== 'O') && (board[row][col+2] == 'S'))
	{
		sos++;//mengecek huruf o di kanan kotak pertama(tengah) dan memeriksa huruf s di kanan kotak ke2(setelah tengah)
	}	
	if((board[row+1][col] == 'O') && (board[row+2][col] == 'S'))
	{
		sos++;//mengecek huruf o di kotak bawah pertama(tengah) dan memeriksa huruf s di kotak bawah  ke2(setelah tengah)
	}
	if((board[row-1][col] == 'O') && (board[row-2][col] == 'S'))
	{
		sos++;//mengecek huruf o di kotak atas pertama(tengah) dan memeriksa huruf s di kotak atas ke2(setelah tengah)
	}
	if((board[row+1][col+1] == 'O') && (board[row+2][col+2] == 'S'))
	{
		sos++;//mengecek huruf o di kotak diagonal bawah kanan pertama dan mengecek huruf s di kotak diagonal bawah kanan ke2(setelah tengah)
	}
	if((board[row-1][col-1] == 'O') && (board[row-2][col-2] == 'S'))
	{
		sos++;//mengecek huruf o di kotak diagonal atas kiri pertama(tengah) dan mengecek huruf s di kotak diagonal atas kiri ke2(setelah tengah)
	}
	if((board[row+1][col-1] == 'O') && (board[row+2][col-2] == 'S'))
	{
		sos++;//mengecek huruf o di kotak diagonal kiri bawah pertama(tengah) dan mengecek huruf s di kotak diagonal kiri bawah ke2(setelah tengah)
	}
	if((board[row-1][col+1] == 'O') && (board[row-2][col+2] == 'S'))
	{
		sos++;//mengecek huruf o di kotak diagonal kanan atas pertama(tengah) dan mengecek huruf s di kotak diagonal kanan atas ke2(setelah tengah)
	}
  }
  else if(symbol == 'O')
  {
	if((board[row+1][col] == 'S') && (board[row-1][col] == 'S'))
	{
		sos++;//memeriksa bawah dan atas
	}
	if((board[row][col+1] == 'S') && (board[row][col-1] == 'S'))
	{
		sos++;//memeriksa kanan dan kiri
	}
	if((board[row+1][col+1] == 'S') && (board[row-1][col-1] == 'S'))
	{
		sos++;//memeriksa diagonal kanan bawah dan kiri atas
	}
	if((board[row+1][col-1] == 'S') && (board[row-1][col+1] == 'S'))
	{
		sos++;//memeriksa diagonal kiri bawah dan kanan atas
	}
  }
  	skor(player,sos);
  
       if (sos>0)
	{
		return 1;//kembali ke player move
	}
	else
	{
		return 0;//kembali ke two_player
	}
}

int skor(int player, int sos){
	
	if (player == 1)
        {
                Player1= Player1+sos;
        }
        else if (player == 2)
        {
                Player2= Player2+sos;
        }
    return;
}
void howtoplay(){
	int i;
	system("cls");
	printf("\t\t\t\t\t\tSelamat Datang di SOS Z \n\n");
	printf("\tSOS Z adalah permainan game sos, permainan ini menggunakan bidang permainan yaitu papan dengan jumlah \n minimal 3x3 dan maksimal 10x10. Jika pemain berhasil menciptakan sos antara kotak terhubung baik vertikal, diagonal, \n maupun horizontal maka pemain mendapat kesempatan untuk menciptakan sos kembali. Apabila pemain tidak bisa membuat \n sos maka giliran pemain lain untuk memainkan permainan ini.\n\n\tCara bermain:\n\n");
	printf("\t1. Pertama, Player1 memilih baris dan kolom yang ingin di isi,\n\t   kemudian Player1 memilih huruf yang akan di inputkan\n");
	printf("\t2. Setelah Player1 menginput huruf, giliran Player2 memilih baris dan kolom serta menginput huruf. \n");
	printf("\t3. Player yang mendapatkan blok sos maka Player tersebut mendapat kesempatan untuk menciptakan sos kembali\n\n");
	printf(" Tekan 1 jika ingin bermain atau tekan 0 untuk keluar aplikasi: ");
	scanf("%d",&i );
	if(i==1){
		besar_papan();
		inis_papan();
		two_player(); 
		if(cek_papan()){//jika papan sudah penuh
			gambar_papan();
			winner();
		}      
	}else if(i==0){
		system("cls");
		printf("\t\tBye!!");
	}
}
 void winner(){
 	printf("\n\n\tPermainan Selesai\n");
 	printf("********************************\n");
 	printf("      Pemain1 %d : %d Pemain2\n",Player1,Player2);
 	printf("********************************\n");
 	if (Player1 > Player2)
	{
		printf("\n\t   PLAYER 1 WON!\n");
	}
	else if (Player2> Player1)
	{
		printf("\n\t   PLAYER 2 WON!\n");
	}
	else
	{
		printf("\n\t  GAME IS DRAW\n");
	}
	printf("\n********************************");
 }
 
