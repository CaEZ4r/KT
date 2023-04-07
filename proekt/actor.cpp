#include "actor.h"

Actor::Actor(){
  if ((key = ftok("act",'A')) < 0){
   perror("Can't get key\n");
   exit(1);
  }
  int err = 0;
  if((mesid = msgget(key, PERM | IPC_CREAT | IPC_EXCL)) < 0){
		err = errno;
		char text[100] = {0};
		sprintf(text, " С какой ошибкой вызван msgget: %u\n", err);
	   perror(text);
    if(errno == EEXIST){
     cout <<"очередь уже есть \n";
			
      if ((mesid = msgget(key,0))< 0){
				perror("Can't create message's queue\n");
        exit(1);
      }
    }else{
			perror("?? Can't create message's queue\n");

      exit(1);
   }
  }
  smsg = sizeof(int) + sizeof(pid_t);
	mSend.pid = getpid();
  mSend.type = mRead.type = 1L;


  	
	if (err == 0){
// Очередь создал именно этот процесс
		
		mSend.number = 1;
 //    mSend.ms[0] = 1;
		if (msgsnd( mesid,(void*)&mSend, smsg , 0) < 0){
			perror("Не могу послать номер 1\n");
      cout<<"Can't write message\n";
     exit(1);
    }
		cout<<"1\n";
		
  }else{
// Очередь создана другим процессом
		mRead.type = 1L;
		cout << "Читаем:";
    n = msgrcv(mesid, &mRead, smsg, mRead.type, 0);
    cout << mRead.number << endl;
		mSend.number = mRead.number + 1;
		cout << "Нас теперь: " << mSend.number << endl;
    printf("send: %hhu\n", mSend.number);
// отсылаем сообщение обратно с новым числом   
		if (msgsnd( mesid, (void*)&mSend, smsg, 0) < 0){
			perror("Не могу прочитать не первый номер\n");
      cout<<"Can't write message\n";
     exit(1);
    }
    cout<<" Я тоже пришел: "<< mSend.number << endl;
  }
};

Actor::~Actor(){
	

// Проверяем сколько процессов еще не удалено
	n = msgrcv(mesid, &mRead, smsg, mRead.type, 0);

// Если число больше 1, то уменьшаем и посылаем новое сообщений  
	if(mRead.number > 1){
		mSend.number = mRead.number - 1;
		cout<<"Посылаем новый номер: "<< mSend.number << endl;
		if (msgsnd(mesid, (void*)&mSend, smsg, 0) < 0){
			perror("Не могу прочитать номер когда ухожу\n");
      cout<<"Can't write message\n";
      exit(1);
    }
    cout << "Я ушел, осталось: " << mRead.number << endl; 
		return;
  }
//else{
    if(msgctl(mesid, IPC_RMID, 0) < 0){
			perror("Не могу удалить очередь\n");
	    printf("Can't delete queue\n");
			
	    exit(1);
    }
	
//  }
};
//Интенсивная работа
void Actor::act(int tm){
		cout<<"Сажусь: "<<tm<<endl;
    sleep(tm);
    cout << "Сел" << endl;
};
