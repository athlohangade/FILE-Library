#include "file.h"
#include "testsuite.h"
void testsuiteread() {
	MYFILE* fd;
	char ch = 'A';
	char str[4096];
	int x, i, z, j;
	float f, k;
	double d, l;
	off_t a;

	printf("TEST 1 :\n");
	fd = myfopen("./testresults/d0", "w");	//to create a file for reading
	if(fd == NULL) {
		printf("Open failed\n");
		return;
	}
	myfwrite("Atharva", 1, 7, fd);
	myfclose(fd);
	
	fd = myfopen("./testresults/d0", "r");	//if no. of bytes to be read are greater than filelength
	if(fd == NULL) {
		printf("Open failed\n");
		return;
	}
	x = myfread(str, 1, 10, fd);
	puts(str);
	printf("%d\t%lu\n", x, myftell(fd));
	myfclose(fd);

	fd = myfopen("./testresults/d0", "r");		//if size of data to be read in is less than actual no. of bytes to be read
	if(fd == NULL) {
		printf("Open failed\n");
		return;
	}
	x = myfread(str, 1, 6, fd);
	puts(str);
	printf("%d\t%lu\n", x, myftell(fd));
	myfclose(fd);
	printf("\n");


	printf("TEST 2 :\n");
	fd = myfopen("./testresults/d1", "w");	//to create a file for reading
	if(fd == NULL) {
		printf("Open failed\n");
		return;
	}
	myfwrite("My name is Atharva Lohangade. I like to play football.", 1, 54, fd);
	myfclose(fd);

	fd = myfopen("./testresults/d1", "r");		//read attempt in same in buffer
	if(fd == NULL) {
		printf("Open failed\n");
		return;
	}
	str[myfread(str, 1, 9, fd)] = '\0';
	puts(str);
	myfwrite("football", 1, 8, fd);		//fails for r mode
	myfseek(fd, 3, SEEK_CUR);
	str[myfread(str, 1, 9, fd)] = '\0';
	puts(str);
	myfclose(fd);
	printf("\n");


	printf("TEST 3 :\n");
	fd = myfopen("./testresults/d1", "r");			//read attempt in same in buffer
	if(fd == NULL) {
		printf("Open failed\n");
		return;
	}
	str[myfread(str, 1, 9, fd)] = '\0';
	puts(str);
	myfseek(fd, 1000, SEEK_SET);
	x = myfread(str, 2, 4, fd);
	if(myfeof(fd))
		printf("%d\n", x);
	myfclose(fd);
	printf("\n");


	printf("TEST 4 :\n");
	fd = myfopen("./testresults/d1", "r");			//read attempt in same in buffer
	if(fd == NULL) {
		printf("Open failed\n");
		return;
	}
	str[myfread(str, 1, 9, fd)] = '\0';
	puts(str);
	printf("%lu\n", myftell(fd));
	myfwrite("Hello", 1, 5, fd);
	printf("%lu\n", myftell(fd));
	myfgetpos(fd, &a);
	myfseek(fd, -13, SEEK_END);
	printf("%lu\n", myftell(fd));
	str[myfread(str, 1, 10, fd)] = '\0';
	puts(str);
	myfsetpos(fd, &a);
	str[myfread(str, 1, 10, fd)] = '\0';
	puts(str);
	myfclose(fd);
	printf("\n");


	printf("TEST 5 :\n");
	fd = myfopen("./testresults/d2", "w");	//to create a file for reading
	if(fd == NULL) {
		printf("Open failed\n");
		return;
	}
	strcpy(str, "Most people in Maharashtra are Hindus and you can see it in the culture of Maharashtra. There are many temples in Maharashtra and some of them are very old. The architecture of these temples is a mixture of architecture from North and South India. The temples also have ideas from Hindu, Buddhist and Jain cultures. Maharashtra has many forts like Raigad and Pratapgad which were very important in the early history of the Maratha Empire and also sea forts like the one at Sindhudurg. The folk music of Maharashtra is mixed. An early piece of Marathi literature is Bhawarthadeepika (known as Dnyaneshwari) by Dnyaneshwar. The religious songs called bhajans by Dnyaneshwar, Tukaram, Namdev,chokhamela,Savta Mali are very popular. Modern Marathi literature also has some great poets and authors likeJyotirao Govindrao Phule,Savitribai Jyotirao Phule,Dr.Bhimrao Ramji Ambedkar, Anna Bhau Sathe,Namdev Dhasal, M.M. Deshmukh,P. L. Deshpande, Kusumagraj, Prahlad Keshav Atre, and Vyankatesh Madgulkar. Many books are published every year in Marathi. The theater, movies, and television in Maharashtra are mostly made in Mumbai, and the actors in each area (like television) can work in the others. Some important people in the movie industry are Dadasaheb Phalke, Dada Kondke, Ashok Saraf, Laxmikant Berde, Sachin Pilgaonkar, Mahesh Kothare and V. Shantaram. Early Marathi theatre had important playwrights (people who write plays) like Kolhatkar, Khadilkar, Deval, Gadkari and Kirloskar. They wrote musical plays called Sangeet Naatak. The music from those plays is called Natyasangeet. Important actors at this time were Bal Gandharva, Keshavrao Bhosle, Bhaurao Kolhatkar, and Dinanath Mangeshkar. Some of the popular Marathi television channels are Mi Marathi and ETV Marathi. They have many kinds of shows: soap operas, cooking, travel, political satire, and game shows. The food of Maharashtra is different in each place. The people in the Konkan region eat more rice and the ones near the ocean eat a lot of fish. In eastern Maharashtra, most people eat a lot of wheat, jowar, and bajra. Other important things people eat in Maharashtra are lentils, onions, tomatoes, potatoes, chilies, garlic, ginger, and aamras. Many people also eat chicken and mutton. In the past, women wore a long sari and men wore a dhoti or pajama with a shirt. Today, women in the cities often wear other clothes like Salwar kameez (dresses from the Punjab), and men in the cities wear trousers and a shirt. Cricket is very popular in Maharashtra. Many people play it and many others watch it. Kabaddi is also popular. Children play Viti-Dandu and Pakada-pakadi (Tag).Hindus in Maharashtra follow the Saka era calendar. Gudi Padwa, Diwali, Rangapanchami, Gokulashtami, and Ganeshotsav are some of the festivals that are celebrated in Maharashtra. Ganeshotsav is the biggest festival. The Hindus celebrate it with reverence and festivity in Maharashtra and it has also become popular in other parts of India. The festival which lasts ten days is in honor of Ganesha, the Hindu god of learning and knowledge.");
	str[1100] = '\0';
	myfwrite(str, 1, 1100, fd);
	myfclose(fd);

	fd = myfopen("./testresults/d2", "r");		//read attempt in next or previous sequential buffer
	if(fd == NULL) {
		printf("Open failed\n");
		return;
	}
	str[myfread(str, 1, 27, fd)] = '\0';
	puts(str);
	myfgetpos(fd, &a);
	myfseek(fd, 1050, SEEK_CUR);
	printf("%lu\n", myftell(fd));
	str[myfread(str, 1, 8, fd)] = '\0';
	puts(str);
	myfseek(fd, -1000, SEEK_END);
	printf("%lu\n", myftell(fd));
	str[myfread(str, 1, 8, fd)] = '\0';
	puts(str);
	myfseek(fd, 1030, SEEK_SET);
	printf("%lu\n", myftell(fd));
	str[myfread(str, 1, 8, fd)] = '\0';
	puts(str);
	myfsetpos(fd, &a);
	printf("%lu\n", myftell(fd));
	str[myfread(str, 1, 8, fd)] = '\0';
	puts(str);
	myfclose(fd);
	printf("\n");


	printf("TEST 6 :\n");
	ch = 'A';
	fd = myfopen("./testresults/d3", "w");	//to create file for reading
	if(fd == NULL) {
		printf("Open failed\n");
		return;
	}
	strcpy(str, "Most people in Maharashtra are Hindus and you can see it in the culture of Maharashtra. There are many temples in Maharashtra and some of them are very old. The architecture of these temples is a mixture of architecture from North and South India. The temples also have ideas from Hindu, Buddhist and Jain cultures. Maharashtra has many forts like Raigad and Pratapgad which were very important in the early history of the Maratha Empire and also sea forts like the one at Sindhudurg. The folk music of Maharashtra is mixed. An early piece of Marathi literature is Bhawarthadeepika (known as Dnyaneshwari) by Dnyaneshwar. The religious songs called bhajans by Dnyaneshwar, Tukaram, Namdev,chokhamela,Savta Mali are very popular. Modern Marathi literature also has some great poets and authors likeJyotirao Govindrao Phule,Savitribai Jyotirao Phule,Dr.Bhimrao Ramji Ambedkar, Anna Bhau Sathe,Namdev Dhasal, M.M. Deshmukh,P. L. Deshpande, Kusumagraj, Prahlad Keshav Atre, and Vyankatesh Madgulkar. Many books are published every year in Marathi. The theater, movies, and television in Maharashtra are mostly made in Mumbai, and the actors in each area (like television) can work in the others. Some important people in the movie industry are Dadasaheb Phalke, Dada Kondke, Ashok Saraf, Laxmikant Berde, Sachin Pilgaonkar, Mahesh Kothare and V. Shantaram. Early Marathi theatre had important playwrights (people who write plays) like Kolhatkar, Khadilkar, Deval, Gadkari and Kirloskar. They wrote musical plays called Sangeet Naatak. The music from those plays is called Natyasangeet. Important actors at this time were Bal Gandharva, Keshavrao Bhosle, Bhaurao Kolhatkar, and Dinanath Mangeshkar. Some of the popular Marathi television channels are Mi Marathi and ETV Marathi. They have many kinds of shows: soap operas, cooking, travel, political satire, and game shows. The food of Maharashtra is different in each place. The people in the Konkan region eat more rice and the ones near the ocean eat a lot of fish. In eastern Maharashtra, most people eat a lot of wheat, jowar, and bajra. Other important things people eat in Maharashtra are lentils, onions, tomatoes, potatoes, chilies, garlic, ginger, and aamras. Many people also eat chicken and mutton. In the past, women wore a long sari and men wore a dhoti or pajama with a shirt. Today, women in the cities often wear other clothes like Salwar kameez (dresses from the Punjab), and men in the cities wear trousers and a shirt. Cricket is very popular in Maharashtra. Many people play it and many others watch it. Kabaddi is also popular. Children play Viti-Dandu and Pakada-pakadi (Tag).Hindus in Maharashtra follow the Saka era calendar. Gudi Padwa, Diwali, Rangapanchami, Gokulashtami, and Ganeshotsav are some of the festivals that are celebrated in Maharashtra. Ganeshotsav is the biggest festival. The Hindus celebrate it with reverence and festivity in Maharashtra and it has also become popular in other parts of India. The festival which lasts ten days is in honor of Ganesha, the Hindu god of learning and knowledge.");
	str[3000] = '\0';
	myfwrite(str, 1, 3000, fd);
	myfclose(fd);

	fd = myfopen("./testresults/d3", "r");			//read attempt in next or previous non-sequential buffer
	if(fd == NULL) {
		printf("Open failed\n");
		return;
	}
	printf("%lu\n", fd->filelength);
	str[myfread(str, 1, 26, fd)] = '\0';
	puts(str);
	myfgetpos(fd, &a);
	myfseek(fd, 2050, SEEK_CUR);
	printf("%lu\n", myftell(fd));
	str[myfread(str, 1, 8, fd)] = '\0';
	puts(str);
	myfseek(fd, -2500, SEEK_END);
	printf("%lu\n", myftell(fd));
	str[myfread(str, 1, 8, fd)] = '\0';
	puts(str);
	myfseek(fd, 2050, SEEK_SET);
	printf("%lu\n", myftell(fd));
	str[myfread(str, 1, 8, fd)] = '\0';
	puts(str);
	myfsetpos(fd, &a);
	printf("%lu\n", myftell(fd));
	str[myfread(str, 1, 8, fd)] = '\0';
	puts(str);
	myfclose(fd);
	printf("\n");


	printf("TEST 7 :\n");
	fd = myfopen("./testresults/d23", "w");	//to create binary file for reading
	if(fd == NULL) {
		printf("Open failed\n");
		return;
	}
	z = 75;
	f = 4589.751;
	d = 23623.145;
	myfwrite(&z, 1, sizeof(int), fd);
	myfwrite(&f, 1, sizeof(float), fd);
	myfwrite(&d, 1, sizeof(double), fd);
	myfclose(fd);

	fd = myfopen("./testresults/d23", "r");	//if no. of bytes to be read are greater than filelength
	if(fd == NULL) {
		printf("Open failed\n");
		return;
	}
	myfread(&j, 1, sizeof(int), fd);
	myfread(&k, 1, sizeof(float), fd);
	myfread(&l, 1, sizeof(double), fd);
	printf("%d\n", j);
	printf("%f\n", k);
	printf("%lf\n", l);
	myfclose(fd);
	printf("\n");


	printf("TEST 8 :\n");
	fd = myfopen("./testresults/d24", "w");		//create file for writing
	if(fd == NULL) {
		printf("Open failed\n");
		return;
	}
	myfwrite("atharva", 1, 7, fd);
	myfclose(fd);

	fd = myfopen("./testresults/d24", "r");		//to test the eof and myfeof function
	if(fd == NULL) {
		printf("Open failed\n");
		return;
	}
	if(myfeof(fd))
		printf("EOF 1\n");
	myfseek(fd, 0, SEEK_END);
	x = myfread(&ch, 1, 2, fd);
	if(myfeof(fd))
		printf("EOF 2\n");
	printf("%d\n", x);
	myfseek(fd, 0, SEEK_SET);
	if(myfeof(fd))
		printf("EOF 3\n");
	myfseek(fd, 5, SEEK_CUR);
	str[x = myfread(str, 1, 5, fd)] = '\0';
	puts(str);
	printf("%d\n", x);
	if(myfeof(fd))
		printf("EOF 4\n");
	myfseek(fd, 50, SEEK_END);
	x = myfread(&ch, 1, 1, fd);
	printf("%d\n", x);
	if(myfeof(fd))
		printf("EOF 5\n");
	myfclose(fd);
	printf("-------------------------------------------------------------\n");
}

void testsuitewrite() {
	MYFILE* fd;
	int x, i, z;
	float f;
	double d;
	char str[4096], ch = 'A';
	off_t a;

	printf("TEST 1 :\n");
	fd = myfopen("./testresults/d4", "w");		//attempt to write more bytes than size of data provided
	if(fd == NULL) {
		printf("Open failed\n");
		return;
	}
	x = myfwrite("Atharva", 1, 9, fd);	//some junk bytes will be written as the size of data provided is less
	printf("%d\n", x);
	myfclose(fd);
	printf("Output in the datafiles\n\n");


	printf("TEST 2 :\n");
	fd = myfopen("./testresults/d5", "w");		//simple write attempt to write some no. of bytes
	if(fd == NULL) {
		printf("Open failed\n");
		return;
	}
	x = myfwrite("Atharva", 1, 7, fd);
	printf("%d\n", x);
	myfseek(fd, 0, SEEK_SET);
	x = myfread(str, 1, 7, fd);		//read attempt fail in w mode
	printf("%d\n", x);
	puts(str);
	myfclose(fd);
	printf("Output in the datafiles\n\n");


	printf("TEST 3 :\n");
	fd = myfopen("./testresults/d6", "w");		//write attempts in the same buffer
	if(fd == NULL) {
		printf("Open failed\n");
		return;
	}
	myfwrite("Atharva", 1, 7, fd);
	myfseek(fd, 4, SEEK_CUR);
	myfwrite("good boy", 1, 8, fd);
	myfseek(fd, 25, SEEK_SET);
	myfwrite("football", 1, 8, fd);
	myfseek(fd, -12, SEEK_END);
	myfwrite("no", 1, 2, fd);
	myfclose(fd);
	printf("Output in the datafiles\n\n");


	printf("TEST 4 :\n");
	fd = myfopen("./testresults/d7", "w");		//write attempt in same buffer
	if(fd == NULL) {
		printf("Open failed\n");
		return;
	}
	myfwrite("Atharva", 1, 10, fd);	//junk bytes will be written as no. of bytes to be written is more than data size
	myfgetpos(fd, &a);
	myfseek(fd, 10, SEEK_CUR);
	myfwrite("bang", 1, 4, fd);
	myfsetpos(fd, &a);
	myfwrite("shoes", 1, 5, fd);
	myfclose(fd);
	printf("Output in the datafiles\n\n");


	printf("TEST 5 :\n");
	fd = myfopen("./testresults/d8", "w");			//attempt to write in next and previous sequential buffer
	if(fd == NULL) {
		printf("open failed....\n");
		return;
	}
	for(i = 0; i < 2000; i++) {
		str[i] = ch;
		ch++;
		if(ch == 91)
			ch = 65;
	}
	myfwrite(str, 1, 2000, fd);
	printf("%ld\n", myftell(fd));
	myfseek(fd, 10, SEEK_SET);
	printf("%ld\n", myftell(fd));
	myfwrite("football", 1, 8, fd);
	myfseek(fd, -20, SEEK_END);
	printf("%ld\n", myftell(fd));
	myfwrite("football", 1, 8, fd);
	myfgetpos(fd, &a);
	myfseek(fd, 0, SEEK_END);
	myfwrite("mango", 1, 5, fd);
	myfsetpos(fd, &a);
	myfwrite(" is a game", 1, 10, fd);
	myfclose(fd);
	printf("Output in the datafiles\n\n");


	printf("TEST 6 :\n");
	ch = 'A';
	fd = myfopen("./testresults/d9", "w");			//attempt to write in next and previous non-sequential buffer
	if(fd == NULL) {
		printf("open failed....\n");
		return;
	}
	strcpy(str, "Most people in Maharashtra are Hindus and you can see it in the culture of Maharashtra. There are many temples in Maharashtra and some of them are very old. The architecture of these temples is a mixture of architecture from North and South India. The temples also have ideas from Hindu, Buddhist and Jain cultures. Maharashtra has many forts like Raigad and Pratapgad which were very important in the early history of the Maratha Empire and also sea forts like the one at Sindhudurg. The folk music of Maharashtra is mixed. An early piece of Marathi literature is Bhawarthadeepika (known as Dnyaneshwari) by Dnyaneshwar. The religious songs called bhajans by Dnyaneshwar, Tukaram, Namdev,chokhamela,Savta Mali are very popular. Modern Marathi literature also has some great poets and authors likeJyotirao Govindrao Phule,Savitribai Jyotirao Phule,Dr.Bhimrao Ramji Ambedkar, Anna Bhau Sathe,Namdev Dhasal, M.M. Deshmukh,P. L. Deshpande, Kusumagraj, Prahlad Keshav Atre, and Vyankatesh Madgulkar. Many books are published every year in Marathi. The theater, movies, and television in Maharashtra are mostly made in Mumbai, and the actors in each area (like television) can work in the others. Some important people in the movie industry are Dadasaheb Phalke, Dada Kondke, Ashok Saraf, Laxmikant Berde, Sachin Pilgaonkar, Mahesh Kothare and V. Shantaram. Early Marathi theatre had important playwrights (people who write plays) like Kolhatkar, Khadilkar, Deval, Gadkari and Kirloskar. They wrote musical plays called Sangeet Naatak. The music from those plays is called Natyasangeet. Important actors at this time were Bal Gandharva, Keshavrao Bhosle, Bhaurao Kolhatkar, and Dinanath Mangeshkar. Some of the popular Marathi television channels are Mi Marathi and ETV Marathi. They have many kinds of shows: soap operas, cooking, travel, political satire, and game shows. The food of Maharashtra is different in each place. The people in the Konkan region eat more rice and the ones near the ocean eat a lot of fish. In eastern Maharashtra, most people eat a lot of wheat, jowar, and bajra. Other important things people eat in Maharashtra are lentils, onions, tomatoes, potatoes, chilies, garlic, ginger, and aamras. Many people also eat chicken and mutton. In the past, women wore a long sari and men wore a dhoti or pajama with a shirt. Today, women in the cities often wear other clothes like Salwar kameez (dresses from the Punjab), and men in the cities wear trousers and a shirt. Cricket is very popular in Maharashtra. Many people play it and many others watch it. Kabaddi is also popular. Children play Viti-Dandu and Pakada-pakadi (Tag).Hindus in Maharashtra follow the Saka era calendar. Gudi Padwa, Diwali, Rangapanchami, Gokulashtami, and Ganeshotsav are some of the festivals that are celebrated in Maharashtra. Ganeshotsav is the biggest festival. The Hindus celebrate it with reverence and festivity in Maharashtra and it has also become popular in other parts of India. The festival which lasts ten days is in honor of Ganesha, the Hindu god of learning and knowledge.");
	str[3000] = '\0';
	myfwrite(str, 1, 3000, fd);
	myfseek(fd, 30, SEEK_SET);
	myfwrite("strawberry", 1, 10, fd);
	myfgetpos(fd, &a);
	myfseek(fd, -20, SEEK_END);
	myfwrite("orange", 1, 6, fd);
	myfseek(fd, 1200, SEEK_SET);
	myfwrite("apple", 1, 5, fd);
	myfseek(fd, 0, SEEK_END);
	myfwrite("football", 1, 8, fd);
	myfsetpos(fd, &a);
	myfwrite("pineapple", 1, 9, fd);
	myfseek(fd, 0, SEEK_END);
	myfwrite(" is a game", 1, 10, fd);	
	myfclose(fd);
	printf("Output in the datafiles\n\n");
	

	printf("TEST 7 :\n");
	fd = myfopen("./testresults/d22", "w");	//if no. of bytes to be read are greater than filelength
	if(fd == NULL) {
		printf("Open failed\n");
		return;
	}
	z = 148;
	f = 756.2038;
	d = 785933.1457;
	myfwrite(&z, 1, sizeof(int), fd);
	myfwrite(&f, 1, sizeof(float), fd);
	myfwrite(&d, 1, sizeof(double), fd);
	myfclose(fd);
	printf("Output in the datafiles\n");
	printf("-------------------------------------------------------------\n");
}

void testsuiteappend() {
	MYFILE *fd;
	int i, x;
	char str[4096], ch = 'A';
	off_t a;
	
	printf("TEST 1 :\n");
	fd = myfopen("./testresults/d10", "a");		//attempt to append in the same buffer
	if(fd == NULL) {
		printf("Open failed\n");
		return;
	}
	myfwrite("Atharva", 1, 7, fd);
	myfwrite("computer", 1, 8, fd);
	myfseek(fd, 0, SEEK_SET);		//no use of fseek in append
	x = myfread(&ch, 1, 1, fd);		//read fails in append mode
	printf("%d\n", x);
	myfwrite("Boom", 1, 4, fd);
	myfwrite("television", 1, 10, fd);		//write more bytes than provided
	myfclose(fd);
	printf("Output in the datafiles\n\n");


	printf("TEST 2 :\n");
	fd = myfopen("./testresults/d11", "a");		//attempt to append in the next sequential buffer
	if(fd == NULL) {
		printf("Open failed\n");
		return;
	}
	for(i = 0; i < 2000; i++) {
		str[i] = ch;
		ch++;
		if(ch == 91)
			ch = 65;
	}
	myfwrite("Atharva", 1, 7, fd);
	myfwrite(str, 1, 2000, fd);
	myfseek(fd, 0, SEEK_SET);		//no use of fseek in append mode as the writing is always at the end
	myfgetpos(fd, &a);
	myfwrite("blanket", 1, 7, fd);
	myfsetpos(fd, &a);			//no use of fsetpos in append mode as the writing is always at the end
	myfwrite("Australia", 1, 9, fd);
	myfclose(fd);
	printf("Output in the datafiles\n\n");


	printf("TEST 3 :\n");
	ch = 'A';
	fd = myfopen("./testresults/d12", "a");		//attempt to append upto a non-sequential buffer i.e. bufno '1' to bufno '3'
	if(fd == NULL) {
		printf("Open failed\n");
		return;
	}
	for(i = 0; i < 3000; i++) {
		str[i] = ch;
		ch++;
		if(ch == 91)
			ch = 65;
	}
	myfwrite("Atharva", 1, 7, fd);
	myfwrite(str, 1, 3000, fd);
	myfseek(fd, 0, SEEK_SET);		//no use of fseek in append mode as the writing is always at the end
	myfgetpos(fd, &a);
	myfwrite("Russia", 1, 6, fd);
	myfsetpos(fd, &a);			//no use of fsetpos in append mode as the writing is always at the end
	myfwrite("Japan", 1, 5, fd);
	myfclose(fd);
	printf("Output in the datafiles\n");
	printf("-------------------------------------------------------------\n");
}
void testsuitereadplus() {
	MYFILE *fd;
	int i;
	char str[4096], ch = 'A';
	off_t a;
	
	printf("TEST 1 :\n");
	fd = myfopen("./testresults/d13", "w");			//to create a file for reading/writing
	if(fd == NULL) {
		printf("Open failed\n");
		return;
	}
	myfwrite("Atharva is a good boy", 1, 21, fd);
	myfclose(fd);

	fd = myfopen("./testresults/d13", "r+");			//read/write attempts in the same buffer
	if(fd == NULL) {
		printf("Open failed\n");
		return;
	}
	str[myfread(str, 1, 7, fd)] = '\0';
	puts(str);
	myfwrite("black", 1, 5, fd);
	myfseek(fd, -10, SEEK_END);
	str[myfread(str, 1, 7, fd)] = '\0';
	puts(str);
	myfwrite("notebook", 1, 8, fd);
	myfseek(fd, 0, SEEK_SET);
	myfwrite("pen", 1, 3, fd);
	myfseek(fd, 2, SEEK_CUR);
	myfwrite("no", 1, 2, fd);
	myfclose(fd);
	printf("\n");


	printf("TEST 2 :\n");
	fd = myfopen("./testresults/d14", "w");			//to create a file for reading/writing
	if(fd == NULL) {
		printf("Open failed\n");
		return;
	}
	myfwrite("Atharva", 1, 7, fd);
	myfclose(fd);

	fd = myfopen("./testresults/d14", "r+");		//read/write attempts in the next and previous sequential buffer
	if(fd == NULL) {
		printf("Open failed\n");
		return;
	}
	myfseek(fd, 0, SEEK_END);
	strcpy(str, "Most people in Maharashtra are Hindus and you can see it in the culture of Maharashtra. There are many temples in Maharashtra and some of them are very old. The architecture of these temples is a mixture of architecture from North and South India. The temples also have ideas from Hindu, Buddhist and Jain cultures. Maharashtra has many forts like Raigad and Pratapgad which were very important in the early history of the Maratha Empire and also sea forts like the one at Sindhudurg. The folk music of Maharashtra is mixed. An early piece of Marathi literature is Bhawarthadeepika (known as Dnyaneshwari) by Dnyaneshwar. The religious songs called bhajans by Dnyaneshwar, Tukaram, Namdev,chokhamela,Savta Mali are very popular. Modern Marathi literature also has some great poets and authors likeJyotirao Govindrao Phule,Savitribai Jyotirao Phule,Dr.Bhimrao Ramji Ambedkar, Anna Bhau Sathe,Namdev Dhasal, M.M. Deshmukh,P. L. Deshpande, Kusumagraj, Prahlad Keshav Atre, and Vyankatesh Madgulkar. Many books are published every year in Marathi. The theater, movies, and television in Maharashtra are mostly made in Mumbai, and the actors in each area (like television) can work in the others. Some important people in the movie industry are Dadasaheb Phalke, Dada Kondke, Ashok Saraf, Laxmikant Berde, Sachin Pilgaonkar, Mahesh Kothare and V. Shantaram. Early Marathi theatre had important playwrights (people who write plays) like Kolhatkar, Khadilkar, Deval, Gadkari and Kirloskar. They wrote musical plays called Sangeet Naatak. The music from those plays is called Natyasangeet. Important actors at this time were Bal Gandharva, Keshavrao Bhosle, Bhaurao Kolhatkar, and Dinanath Mangeshkar. Some of the popular Marathi television channels are Mi Marathi and ETV Marathi. They have many kinds of shows: soap operas, cooking, travel, political satire, and game shows. The food of Maharashtra is different in each place. The people in the Konkan region eat more rice and the ones near the ocean eat a lot of fish. In eastern Maharashtra, most people eat a lot of wheat, jowar, and bajra. Other important things people eat in Maharashtra are lentils, onions, tomatoes, potatoes, chilies, garlic, ginger, and aamras. Many people also eat chicken and mutton. In the past, women wore a long sari and men wore a dhoti or pajama with a shirt. Today, women in the cities often wear other clothes like Salwar kameez (dresses from the Punjab), and men in the cities wear trousers and a shirt. Cricket is very popular in Maharashtra. Many people play it and many others watch it. Kabaddi is also popular. Children play Viti-Dandu and Pakada-pakadi (Tag).Hindus in Maharashtra follow the Saka era calendar. Gudi Padwa, Diwali, Rangapanchami, Gokulashtami, and Ganeshotsav are some of the festivals that are celebrated in Maharashtra. Ganeshotsav is the biggest festival. The Hindus celebrate it with reverence and festivity in Maharashtra and it has also become popular in other parts of India. The festival which lasts ten days is in honor of Ganesha, the Hindu god of learning and knowledge.");
	str[2000] = '\0';
	myfwrite(str, 1, 2000, fd);
	myfseek(fd, 20, SEEK_SET);
	myfwrite("bottle", 1, 6, fd);
	str[myfread(str, 1, 1023, fd)] = '\0';
	puts(str);
	printf("%lu\n", myftell(fd));
	myfgetpos(fd, &a);
	myfseek(fd, 10, SEEK_END);		// fseek ahead of the filelength so write will put junk data in between
	myfwrite("chair", 1, 5, fd);
	myfsetpos(fd, &a);
	str[myfread(str, 1, 10, fd)] = '\0';
	puts(str);
	myfwrite("table", 1, 5, fd);
	myfclose(fd);
	printf("\n");


	printf("TEST 3 :\n");
	ch = 'A';
	fd = myfopen("./testresults/d15", "w");		//to create a file for reading/writing
	if(fd == NULL) {
		printf("Open failed\n");
		return;
	}
	myfclose(fd);

	fd = myfopen("./testresults/d15", "r+");		//read/write attempts in the next and previous non-sequential buffer
	if(fd == NULL) {
		printf("Open failed\n");
		return;
	}
	for(i = 0; i < 3000; i++) {
		str[i] = ch;
		ch++;
		if(ch == 91)
			ch = 65;
	}
	str[i] = '\0';
	myfwrite(str, 1, 3000, fd);
	myfseek(fd, 20, SEEK_SET);
	myfwrite("bottle", 1, 6, fd);
	str[myfread(str, 1, 10, fd)] = '\0';
	puts(str);
	printf("%lu\n", myftell(fd));
	myfseek(fd, -7, SEEK_END);
	str[myfread(str, 1, 5, fd)] = '\0';
	puts(str);
	myfwrite("chair", 1, 5, fd);
	myfclose(fd);
	printf("-------------------------------------------------------------\n");
}
void testsuitewriteplus() {
	MYFILE *fd;
	int i;
	char str[4096], ch = 'A';
	off_t a; 
	printf("TEST 1 :\n");
	fd = myfopen("./testresults/d16", "w+");			//read/write attempts in the same buffer
	if(fd == NULL) {
		printf("Open failed\n");
		return;
	}
	myfwrite("Delhi is capital of India", 1, 25, fd);
	myfseek(fd, 6, SEEK_SET);
	str[myfread(str, 1, 10, fd)] = '\0';
	puts(str);
	myfgetpos(fd, &a);
	myfseek(fd, 0, SEEK_END);
	myfwrite("notebook", 1, 8, fd);
	myfsetpos(fd, &a);
	myfwrite("pen", 1, 3, fd);
	str[myfread(str, 1, 6, fd)] = '\0';
	puts(str);
	myfclose(fd);
	printf("\n");


	printf("TEST 2 :\n");
	fd = myfopen("./testresults/d17", "w+");		//read/write attempts in the next and previous sequential buffer
	if(fd == NULL) {
		printf("Open failed\n");
		return;
	}
	strcpy(str, "Most people in Maharashtra are Hindus and you can see it in the culture of Maharashtra. There are many temples in Maharashtra and some of them are very old. The architecture of these temples is a mixture of architecture from North and South India. The temples also have ideas from Hindu, Buddhist and Jain cultures. Maharashtra has many forts like Raigad and Pratapgad which were very important in the early history of the Maratha Empire and also sea forts like the one at Sindhudurg. The folk music of Maharashtra is mixed. An early piece of Marathi literature is Bhawarthadeepika (known as Dnyaneshwari) by Dnyaneshwar. The religious songs called bhajans by Dnyaneshwar, Tukaram, Namdev,chokhamela,Savta Mali are very popular. Modern Marathi literature also has some great poets and authors likeJyotirao Govindrao Phule,Savitribai Jyotirao Phule,Dr.Bhimrao Ramji Ambedkar, Anna Bhau Sathe,Namdev Dhasal, M.M. Deshmukh,P. L. Deshpande, Kusumagraj, Prahlad Keshav Atre, and Vyankatesh Madgulkar. Many books are published every year in Marathi. The theater, movies, and television in Maharashtra are mostly made in Mumbai, and the actors in each area (like television) can work in the others. Some important people in the movie industry are Dadasaheb Phalke, Dada Kondke, Ashok Saraf, Laxmikant Berde, Sachin Pilgaonkar, Mahesh Kothare and V. Shantaram. Early Marathi theatre had important playwrights (people who write plays) like Kolhatkar, Khadilkar, Deval, Gadkari and Kirloskar. They wrote musical plays called Sangeet Naatak. The music from those plays is called Natyasangeet. Important actors at this time were Bal Gandharva, Keshavrao Bhosle, Bhaurao Kolhatkar, and Dinanath Mangeshkar. Some of the popular Marathi television channels are Mi Marathi and ETV Marathi. They have many kinds of shows: soap operas, cooking, travel, political satire, and game shows. The food of Maharashtra is different in each place. The people in the Konkan region eat more rice and the ones near the ocean eat a lot of fish. In eastern Maharashtra, most people eat a lot of wheat, jowar, and bajra. Other important things people eat in Maharashtra are lentils, onions, tomatoes, potatoes, chilies, garlic, ginger, and aamras. Many people also eat chicken and mutton. In the past, women wore a long sari and men wore a dhoti or pajama with a shirt. Today, women in the cities often wear other clothes like Salwar kameez (dresses from the Punjab), and men in the cities wear trousers and a shirt. Cricket is very popular in Maharashtra. Many people play it and many others watch it. Kabaddi is also popular. Children play Viti-Dandu and Pakada-pakadi (Tag).Hindus in Maharashtra follow the Saka era calendar. Gudi Padwa, Diwali, Rangapanchami, Gokulashtami, and Ganeshotsav are some of the festivals that are celebrated in Maharashtra. Ganeshotsav is the biggest festival. The Hindus celebrate it with reverence and festivity in Maharashtra and it has also become popular in other parts of India. The festival which lasts ten days is in honor of Ganesha, the Hindu god of learning and knowledge.");
	str[2000] = '\0';
	myfwrite(str, 1, 2000, fd);
	myfseek(fd, 20, SEEK_SET);
	myfwrite("shoes", 1, 5, fd);
	str[myfread(str, 1, 23, fd)] = '\0';
	puts(str);
	printf("%lu\n", myftell(fd));
	myfgetpos(fd, &a);
	myfseek(fd, 0, SEEK_END);
	myfread(&ch, 1, 1, fd);
	if(myfeof(fd)) {
		myfwrite("plate", 1, 5, fd);
	}
	myfsetpos(fd, &a);
	myfwrite("table", 1, 5, fd);
	myfclose(fd);
	printf("\n");


	printf("TEST 3 :\n");
	ch = 'A';
	fd = myfopen("./testresults/d18", "w+");		//read/write attempts in the next and previous non-sequential buffer
	if(fd == NULL) {
		printf("Open failed\n");
		return;
	}
	strcpy(str, "Most people in Maharashtra are Hindus and you can see it in the culture of Maharashtra. There are many temples in Maharashtra and some of them are very old. The architecture of these temples is a mixture of architecture from North and South India. The temples also have ideas from Hindu, Buddhist and Jain cultures. Maharashtra has many forts like Raigad and Pratapgad which were very important in the early history of the Maratha Empire and also sea forts like the one at Sindhudurg. The folk music of Maharashtra is mixed. An early piece of Marathi literature is Bhawarthadeepika (known as Dnyaneshwari) by Dnyaneshwar. The religious songs called bhajans by Dnyaneshwar, Tukaram, Namdev,chokhamela,Savta Mali are very popular. Modern Marathi literature also has some great poets and authors likeJyotirao Govindrao Phule,Savitribai Jyotirao Phule,Dr.Bhimrao Ramji Ambedkar, Anna Bhau Sathe,Namdev Dhasal, M.M. Deshmukh,P. L. Deshpande, Kusumagraj, Prahlad Keshav Atre, and Vyankatesh Madgulkar. Many books are published every year in Marathi. The theater, movies, and television in Maharashtra are mostly made in Mumbai, and the actors in each area (like television) can work in the others. Some important people in the movie industry are Dadasaheb Phalke, Dada Kondke, Ashok Saraf, Laxmikant Berde, Sachin Pilgaonkar, Mahesh Kothare and V. Shantaram. Early Marathi theatre had important playwrights (people who write plays) like Kolhatkar, Khadilkar, Deval, Gadkari and Kirloskar. They wrote musical plays called Sangeet Naatak. The music from those plays is called Natyasangeet. Important actors at this time were Bal Gandharva, Keshavrao Bhosle, Bhaurao Kolhatkar, and Dinanath Mangeshkar. Some of the popular Marathi television channels are Mi Marathi and ETV Marathi. They have many kinds of shows: soap operas, cooking, travel, political satire, and game shows. The food of Maharashtra is different in each place. The people in the Konkan region eat more rice and the ones near the ocean eat a lot of fish. In eastern Maharashtra, most people eat a lot of wheat, jowar, and bajra. Other important things people eat in Maharashtra are lentils, onions, tomatoes, potatoes, chilies, garlic, ginger, and aamras. Many people also eat chicken and mutton. In the past, women wore a long sari and men wore a dhoti or pajama with a shirt. Today, women in the cities often wear other clothes like Salwar kameez (dresses from the Punjab), and men in the cities wear trousers and a shirt. Cricket is very popular in Maharashtra. Many people play it and many others watch it. Kabaddi is also popular. Children play Viti-Dandu and Pakada-pakadi (Tag).Hindus in Maharashtra follow the Saka era calendar. Gudi Padwa, Diwali, Rangapanchami, Gokulashtami, and Ganeshotsav are some of the festivals that are celebrated in Maharashtra. Ganeshotsav is the biggest festival. The Hindus celebrate it with reverence and festivity in Maharashtra and it has also become popular in other parts of India. The festival which lasts ten days is in honor of Ganesha, the Hindu god of learning and knowledge.");
	str[3000] = '\0';
	myfwrite(str, 1, 3000, fd);
	myfseek(fd, 20, SEEK_SET);
	myfwrite("bottle", 1, 6, fd);
	str[myfread(str, 1, 10, fd)] = '\0';
	puts(str);
	printf("%lu\n", myftell(fd));
	myfseek(fd, -7, SEEK_END);
	str[myfread(str, 1, 5, fd)] = '\0';
	puts(str);
	myfwrite("cricket", 1, 7, fd);
	myfclose(fd);
	printf("-------------------------------------------------------------\n");
}
void testsuiteappendplus() {
	MYFILE *fd;
	char str[4096], ch = 'A';
	int i, x;
	off_t a;
	printf("TEST 1 :\n");
	fd = myfopen("./testresults/d19", "a+");			//read/append attempts in the same buffer
	if(fd == NULL) {
		printf("Open failed\n");
		return;
	}
	myfwrite("Delhi is capital of India", 1, 25, fd);
	myfseek(fd, 0, SEEK_SET);
	str[myfread(str, 1, 5, fd)] = '\0';
	puts(str);
	myfgetpos(fd, &a);
	myfwrite("cricket", 1, 7, fd);
	myfsetpos(fd, &a);
	str[myfread(str, 1, 11, fd)] = '\0';
	puts(str);
	myfwrite("pen", 1, 3, fd);
	myfseek(fd, 2, SEEK_SET);
	str[myfread(str, 1, 7, fd)] = '\0';
	puts(str);
	myfclose(fd);
	printf("\n");


	printf("TEST 2 :\n");
	fd = myfopen("./testresults/d20", "w");	//to create file for appending/reading
	if(fd == NULL) {
		printf("Open failed\n");
		return;
	}
	myfwrite("Atharva is a good boy", 1, 21, fd);
	myfclose(fd);

	fd = myfopen("./testresults/d20", "a+");		//read/append attempts in the next and previous sequential buffer
	if(fd == NULL) {
		printf("Open failed\n");
		return;
	}
	for(i = 0; i < 2000; i++) {
		str[i] = ch;
		ch++;
		if(ch == 91)
			ch = 65;
	}
	str[i] = '\0';
	myfwrite(str, 1, 2000, fd);
	myfseek(fd, 20, SEEK_SET);
	myfwrite("shoes", 1, 5, fd);
	myfseek(fd, 10, SEEK_SET);
	str[myfread(str, 1, 20, fd)] = '\0';
	puts(str);
	myfgetpos(fd, &a);
	myfwrite("bottle", 1, 6, fd);
	if(myfeof(fd)) {
		myfwrite("plate", 1, 5, fd);
	}
	myfsetpos(fd, &a);
	str[myfread(str, 1, 20, fd)] = '\0';
	puts(str);
	myfclose(fd);
	printf("\n");


	printf("TEST 3 :\n");
	ch = 'A';
	fd = myfopen("./testresults/d21", "a+");		//read/append attempts in the next and previous non-sequential buffer
	if(fd == NULL) {
		printf("Open failed\n");
		return;
	}
	strcpy(str, "Most people in Maharashtra are Hindus and you can see it in the culture of Maharashtra. There are many temples in Maharashtra and some of them are very old. The architecture of these temples is a mixture of architecture from North and South India. The temples also have ideas from Hindu, Buddhist and Jain cultures. Maharashtra has many forts like Raigad and Pratapgad which were very important in the early history of the Maratha Empire and also sea forts like the one at Sindhudurg. The folk music of Maharashtra is mixed. An early piece of Marathi literature is Bhawarthadeepika (known as Dnyaneshwari) by Dnyaneshwar. The religious songs called bhajans by Dnyaneshwar, Tukaram, Namdev,chokhamela,Savta Mali are very popular. Modern Marathi literature also has some great poets and authors likeJyotirao Govindrao Phule,Savitribai Jyotirao Phule,Dr.Bhimrao Ramji Ambedkar, Anna Bhau Sathe,Namdev Dhasal, M.M. Deshmukh,P. L. Deshpande, Kusumagraj, Prahlad Keshav Atre, and Vyankatesh Madgulkar. Many books are published every year in Marathi. The theater, movies, and television in Maharashtra are mostly made in Mumbai, and the actors in each area (like television) can work in the others. Some important people in the movie industry are Dadasaheb Phalke, Dada Kondke, Ashok Saraf, Laxmikant Berde, Sachin Pilgaonkar, Mahesh Kothare and V. Shantaram. Early Marathi theatre had important playwrights (people who write plays) like Kolhatkar, Khadilkar, Deval, Gadkari and Kirloskar. They wrote musical plays called Sangeet Naatak. The music from those plays is called Natyasangeet. Important actors at this time were Bal Gandharva, Keshavrao Bhosle, Bhaurao Kolhatkar, and Dinanath Mangeshkar. Some of the popular Marathi television channels are Mi Marathi and ETV Marathi. They have many kinds of shows: soap operas, cooking, travel, political satire, and game shows. The food of Maharashtra is different in each place. The people in the Konkan region eat more rice and the ones near the ocean eat a lot of fish. In eastern Maharashtra, most people eat a lot of wheat, jowar, and bajra. Other important things people eat in Maharashtra are lentils, onions, tomatoes, potatoes, chilies, garlic, ginger, and aamras. Many people also eat chicken and mutton. In the past, women wore a long sari and men wore a dhoti or pajama with a shirt. Today, women in the cities often wear other clothes like Salwar kameez (dresses from the Punjab), and men in the cities wear trousers and a shirt. Cricket is very popular in Maharashtra. Many people play it and many others watch it. Kabaddi is also popular. Children play Viti-Dandu and Pakada-pakadi (Tag).Hindus in Maharashtra follow the Saka era calendar. Gudi Padwa, Diwali, Rangapanchami, Gokulashtami, and Ganeshotsav are some of the festivals that are celebrated in Maharashtra. Ganeshotsav is the biggest festival. The Hindus celebrate it with reverence and festivity in Maharashtra and it has also become popular in other parts of India. The festival which lasts ten days is in honor of Ganesha, the Hindu god of learning and knowledge.");
	str[3000] = '\0';
	myfwrite("Virat Kohli is the best cricket player.", 1, 39, fd);
	myfwrite(str, 1, 3000, fd);
	myfseek(fd, 20, SEEK_SET);
	myfwrite("bottle", 1, 6, fd);
	myfseek(fd, 10, SEEK_SET);
	str[myfread(str, 1, 10, fd)] = '\0';
	puts(str);
	myfgetpos(fd, &a);
	myfwrite("light", 1, 5, fd);
	myfsetpos(fd, &a);
	str[myfread(str, 1, 10, fd)] = '\0';
	puts(str);
	myfseek(fd, 7, SEEK_END);
	myfwrite("chair", 1, 5, fd);
	myfclose(fd);
	printf("\n");	
}
