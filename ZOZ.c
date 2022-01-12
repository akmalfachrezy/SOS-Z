#include <stdio.h>

void inispapan ();
void gambarpapan ();
int square_valid ();
int cekpapan ();
int find_sos (int, int, char);
void two_player ();
void howtoplay ();
int find_square ();
void player_move();

char board[5][5];
int Player1, Player2, players, n;

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
		inispapan();
		players=2;
		two_player();        
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

void inispapan()
{
	system("cls");
	int row,col;
	n=3;
	for (row = 0; row < n; row++)
	{
		for (col=0; col<n; col++)
		{
			board[row][col]=' ';
		}
	}
	Player1 = 0;
	Player2 = 0;
	
	return;
}

void gambarpapan()
{
	int row, col,ii;
	printf("\n");
	for (row=0; row<n; row++)
	{
		printf(" |"); 
		for (col=0; col<n; col++)
		{
			printf(" %c |",board[row][col]);
		}
		printf(" \n");
		if (row != n)
		{
			printf(" ");
			for(ii=0; ii<((n*4)+1); ii++)
			{ 
				printf("-");
			}
			printf(" \n");
		}
	}
	printf("\n");		
	 if (players == 2)
	{
		printf("Player1 %d : %d Player2\n", Player1, Player2);
	}
	return;
}

int cekpapan()//mengecek apakah kotak sudah terisi atau belum
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
	
	return 1;
}

int square_valid (int square)
{//pengecekan apakah kotak yang akan diisi kosong
   int row, col;
   
   if(square>0 && square<((n*n)+1))
   {	
	row = (square-1)/n;
	col = (square-1)%n;

	if (board[row][col]==' ')
	{
		return 1;
	}
	else 
	{
		return 0;
	} 
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
		if(cekpapan())//mengecek papan apakah sudah terisi atau belum
		{ 
			return;
		}
		player_move(2);
	}while (!cekpapan());

	return;	
}

void player_move(int player)
{
  int square;
  int row, col;
  char symbol;

  do
  {
	gambarpapan(); //memanggil modul gambarpapan
        printf("\nPlayer %d, pilih kotak yang akan diisi: \n",player);

	do
	{
		scanf("%d", &square);
	}while (!square_valid(square));

	row = (square-1)/n;// baris yan ingin di input
	col = (square-1)%n;// kolom yan ingin di input
	
	printf("Pilih huruf yang ingin dimasukkan di kotak %d (S or O) \n", square);
	do 
	{
		symbol = getchar();
	}while ((symbol != 'S') && (symbol != 's') && (symbol != 'O') && (symbol != 'o') && (symbol != '0')); 
	//ulangi sampai pemain memasukkan huruf s atau o

	if((symbol == 'S') || (symbol == 's'))
	{
		symbol = 'S';
	}
	else 
	{
		symbol = 'O';	
	}

	board[row][col] = symbol; //baris ke[row][col] diisi dengan symbol
   }while(find_sos (square, player, symbol)); //ulangi sampai menemukan sos, jika tidak kembali ke modul two_player
   
   return;
}
int find_sos (int square, int player, char symbol)
{
	int row,col,sos;
	
	row = (square-1)/n;
	col = (square-1)%n;
	sos = 0;
	
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



        if (player == 1)
        {
                Player1= Player1+sos;
        }
        else if (player == 2)
        {
                 Player2= Player2+sos;
        }

	if (sos>0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
void howtoplay(){
	int i;
	system("cls");
	printf("\t\t\t\t\t\tSelamat Datang di ZOZ \n\n");
	printf("\tZOZ adalah permainan game sos, permainan ini menggunakan bidang permainan yaitu papan dengan jumlah minimal 3x3.\nJika pemain berhasil menciptakan sos antara kotak terhubung baik vertikal, diagonal, maupun horizontal maka pemain \nmendapat kesempatan untuk menciptakan sos kembali. Apabila pemain tidak bisa membuat sos maka giliran pemain lain untuk memainkan permainan ini. Cara bermain:\n\n");
	printf("1. Pertama, pemain 1 memilih kotak yang ingin di isi,\n  kemudian pemain memilih huruf yang akan di inputkan\n");
	printf("2. Setelah Player1 menginput huruf, giliran Player2 menginput huruf, begitu seterusnya. \n\n");
	printf("jika ingin bermain tekan 1, jika ingin keluar tekan 0: ");
	scanf("%d",&i );
	if(i==1){
		inispapan();
		players=2;
		two_player(); 
	}else if(i==0){
		system("cls");
		printf("\t\tBye!!");
	}
}

