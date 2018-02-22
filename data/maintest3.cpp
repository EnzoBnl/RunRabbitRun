#include"pong3.h"

/*
cd prog/c/sdl/rrr/data
g++ -c -w -std=c++11 pong3.cpp
g++ -w pong3.o maintest3.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL_mixer -std=c++11 
a

item *it;
item *it2;
int i=min(0,10);
int d=0;
void musiqueff(Fenetre *f)
{
	
	if(f->actionsList[musiquef]==1)
	{
		f->setBG("bgkaw.bmp",50);
		Mix_Music *musique= Mix_LoadMUS("Kyoukai no Kanata Ending Full.wav");
		Mix_PlayMusic(musique, -1);
		f->actionsList[musiquef]=0;
		 it=new item(f,"it",0,100,100,0);
		 it->addApparence("block","r/lee.bmp",0,255,0,0,255); 
		 f->blit(it);
	}
	f->delAction(musiquef);
	f->addAction(musiquef,addAction_default);
	
	while(f->nextEvent()!=0)
	{ 

		 if(f->e->type==SDL_KEYDOWN and f->e->key.repeat == 0)
		 { 
			if(f->e->key.keysym.sym==SDLK_u)
			{
				 it=new item(f,"it",0,100,100,0);
				it->addApparence("textescore","monoligne\nmonoligne\nmonoligne\nvmonoligne\nmonoligne\nmonoligne","Square.ttf",30,255,250,100,100);
				it->changerApparence('e',"textescore");
				f->blit(it);
				it->changerVitesseXY(1,1);
				 // it=new item(f,"it"+ItoS(rrand(0,10000)),1,100,100,1);
				// it->addApparence("leequicours",{"bgr.bmp","ball.bmp"},{200,200},{0,0},{50,255},0,0,255);
				// cout<<"yolo"<<it->anis["leequicours"].durees[0]<<" "<<it->anis["leequicours"].durees[1]<<endl;
				// cout<<"yolo"<<it->anis["leequicours"].troncats[0]<<" "<<it->anis["leequicours"].troncats[1]<<endl;
				// it->changerApparence('a',"leequicours");
				 // f->blit(it);
				
			}

			 // it=new item(f,"it"+ItoS(f->t),0,rrand(0,800),rrand(0,400));
		 // it->addApparence("block","bgkaw.bmp",0,255,0,0,255); 
		 }
		 if(f->e->type==SDL_KEYUP and f->e->key.repeat == 0)
		 {
				
		 }
		 if(f->e->type==SDL_MOUSEBUTTONUP and f->e->key.repeat == 0)
		 {
			 // f->resetImgs();
			d=1;
			 		// it=new item(f,"it",0,100,100,1);
		 // it->addApparence("block","r/lee.bmp",0,255,0,0,255); 
		 // f->blit(it);
		 }
		  if(f->e->type==SDL_MOUSEBUTTONDOWN and f->e->key.repeat == 0)
		 {
			d=0;
		 }
		 
		
		
	
	}
	
	if(d)
	{it->moveAuMax(100,100);it->accelerer(-0.8,-0.8);}
}
*/


item *rabbit;
item*haut;
item*droite;
static const int resl=16;
static const int resc=27;

item* bricks[resl][resc];

item* textesupersaut;
item* textescore;
item* textebestscore;

int jumpdispo=1;
int superjumpdispo=1;

int etat[4]={1,0,0,0};
int tailleSprite=60;
int gravite=18;
int troncay=13,troncax=13;
int scroll=-180;
int t;
int score=0;
int bestscore;


void leerabbit(Fenetre *f)
{
	
	colToken col;int c;
	if(f->actionsList[leerabbit]==1)
	{
		
	}
	if(f->actionsList[leerabbit]==1 or f->actionsList[leerabbit]==2)
	{
		haut=new item(f,"H",0,0,0,1);
		droite=new item(f,"D",0,0,0,1);
		rabbit=new item(f,"rabbit",0,500,100,0);
		textesupersaut=new item(f,"textesupersaut",0,0,0,0);
		textescore=new item(f,"textescore",0,500,0,0);
		textebestscore=new item(f,"textebestscore",0,1000,0,0);		
		haut->changerRect(0,-100,f->largeur,100);
		droite->changerRect(f->largeur,0,100,f->hauteur);
		f->addObstacleInvisible(haut);
		f->addObstacleInvisible(droite);
		
		rabbit->addApparence("arret","ra/r5.bmp",troncay,255,255,255,255);
		rabbit->addApparence("droite",{"ra/r4.bmp","ra/r5.bmp","ra/r6.bmp"},
		{110,110,110},{troncay,troncay,troncay},{255,255,255},255,255,255);
		
		rabbit->addApparence("gauche",{"ra/r1.bmp","ra/r2.bmp","ra/r3.bmp"},
		{110,110,110},{troncay,troncay,troncay},{255,255,255},255,255,255);
		rabbit->changerVitesseXY(0,0);
		f->blit(rabbit);
		t=f->t;
		score=0;
		jumpdispo=1;
		superjumpdispo=1;
		fstream fich;
		fich.open("score.txt", ios::in);
		fich>>bestscore;
		fich.close();
		srand((int)(f->t*10)%1000);
		f->actionsList[leerabbit]=0;
		for(int i=0;i<resl;i++)
		{	
			for(int j=0;j<resc;j++)
			{

				bricks[i][j]=new item(f,ItoS(resc*i+j),1,j*tailleSprite,i*tailleSprite,1);
				bricks[i][j]->addApparence("base","rock6.bmp",0,230,255,255,255);
				
				if((int)(rrand(0,100)>80))//j<pow(i/2,2) or j==10-i*3))
				{
					f->blit(bricks[i][j]);
					
				}
			}
		}
		f->setBG("bgkaw.bmp",255);
		
		textesupersaut->addApparence("dispo","SUPER JUMP:\nDISPO","Square.ttf",30,255,150,150,150);
		textesupersaut->addApparence("indispo","SUPER JUMP:\nINDISPONIBLE","Square.ttf",30,255,150,150,150);
		f->blit(textesupersaut);
		
		textescore->addApparence("base","SC="+ItoS(score),"Square.ttf",30,255,150,150,200);
		textescore->delApparence('e',"dispo");
		textescore->addApparence("base","SCORE="+ItoS(score),"Square.ttf",30,255,150,150,200);
		f->blit(textescore);
		
		textebestscore->addApparence("base","BESTSCORE="+ItoS(bestscore),"Square.ttf",30,255,230,160,180);
		f->blit(textebestscore);
	}
	
	rabbit->move(scroll,0);
	for(int i=0;i<resl;i++)
	{
		for(int j=0;j<resc;j++)
		{
			bricks[i][j]->move(scroll,0);
			if(bricks[i][j]->etat.rect.x<=-tailleSprite)
			{
				score++;
				textescore->addApparence("base","SCORE="+ItoS(score),"Square.ttf",30,255,150,150,200);
				if((rrand(0,5000+3*score)<=1800))
				{
					bricks[i][j]->go((resc-1)*tailleSprite,i*tailleSprite);
					f->blit(bricks[i][j]);
				}
				else
				{
					f->unBlit(bricks[i][j]);
					bricks[i][j]->go((resc-1)*tailleSprite,i*tailleSprite);
				}
			}
		}
	} 
	while(f->nextEvent()!=0)
	{

		if (f->e->type==SDL_KEYDOWN)
		{
			if(f->e->key.keysym.sym==SDLK_a && f->e->key.repeat == 0)
			{f->finMainLoop();}
			if(f->e->key.keysym.sym==SDLK_q && f->e->key.repeat == 0)
			{etat[1]=1;}
			if(f->e->key.keysym.sym==SDLK_d && f->e->key.repeat == 0)
			{etat[2]=1;}
			if(f->e->key.keysym.sym==SDLK_z && f->e->key.repeat == 0 and jumpdispo==1 and superjumpdispo==1)
			{
				t=f->t;
				jumpdispo=0;
				superjumpdispo=0;
				textesupersaut->changerApparence('e',"indispo");
				rabbit->changerVitesseXY(rabbit->etat.vitesse.vx*10*score/5000,-1000);
			}
			if(f->e->key.keysym.sym==SDLK_n && f->e->key.repeat == 0)
			{rabbit->changerVitesseY(500);}
			if(f->e->key.keysym.sym==SDLK_SPACE && f->e->key.repeat == 0 and jumpdispo==1)
			{
				jumpdispo=0;
				rabbit->changerVitesseY(-500);
			}
			
		}
		if (f->e->type==SDL_KEYUP)
		{
			if(f->e->key.keysym.sym==SDLK_q && f->e->key.repeat == 0){etat[1]=0;}
			if(f->e->key.keysym.sym==SDLK_d && f->e->key.repeat == 0){etat[2]=0;}	
		}
	}
	if(superjumpdispo==0 and f->t-t>10000)
	{
		superjumpdispo=1;
		t=f->t;
		textesupersaut->changerApparence('e',"dispo");
	}
	etat[0]=0;
	if((etat[1]==0 and etat[2]==0) or (etat[1]!=0 and etat[2]!=0))
	{
		rabbit->changerVitesseX(0);
		etat[0]=1;
		rabbit->changerApparence('i',"arret");
	}
	else if(etat[1]!=0)
	{
		rabbit->changerVitesseX(-450);
		rabbit->changerApparence('a',"gauche");
	}
	else if(etat[2]!=0)
	{
		rabbit->changerVitesseX(450);
		rabbit->changerApparence('a',"droite");
	}
	
	if(c=rabbit->moveAuMax())
	{
		if(c==2)
		{
			rabbit->changerVitesseXY(0,0);
		}
		else if(c==1)
		{
			rabbit->changerVitesseX(0);
		}
		else
		{
			rabbit->changerVitesseY(0);
		}
		
		
	}
	
	while((col=rabbit->nextCol()).obstacle)
	{
		if(col.obstacle!=haut and col.obstacle!=droite)
		{
			jumpdispo=1;
			if(col.axe=='y')
			{
				if (fabs(col.vitesse.vy)>500)
				{
					f->unBlit(col.obstacle);
				}
			}
		}
	}
	rabbit->accelerer(0,gravite);
	if(rabbit->etat.rect.x<=-30 or rabbit->etat.rect.y>=resl*tailleSprite)
	{
		if(score>bestscore)
		{
			fstream fich;
			fich.open("score.txt", ios::out);
			fich<<score;
			fich.close();
		}
		f->resetImgs();
		f->actionsList[leerabbit]=2;
	}
}

item *menuTexte;
void menu(Fenetre *f)
{
	if(f->actionsList[menu]==1)
	{
		printf("1\n");
		f->setBG("bgkaw.bmp",100);
		menuTexte=new item(f,"menu",0,0,0,0);
		menuTexte->addApparence("base","Q : Gauche\nD : Droite\nSPACE : Saut simple\nN : accelerer vers le bas\nZ : SUPER SAUT \n(10 secondes entre deux relances)\n\nPour relancer un saut il faut \ntoucher un bloc \nTaper trop vite contre un bloc le fait disparaitre ! \n\n\n\n\nAppuie sur ESPACE pour DEMARRER !\n\n\(Appuie sur A pour QUITTER)","TravelingTypewriter.otf",55,255,255,255,255);
		f->blit(menuTexte);
		f->actionsList[menu]=0;
		printf("1\n");
	}
	while(f->nextEvent()!=0)
	{
		if (f->e->type==SDL_KEYDOWN)
		{
			
			if(f->e->key.keysym.sym==SDLK_SPACE && f->e->key.repeat == 0)
			{
				menuTexte->freeItem();
				f->delAction(menu);
				f->addAction(leerabbit,1);}
			if(f->e->key.keysym.sym==SDLK_a && f->e->key.repeat == 0)
			{
				f->finMainLoop();
			}
		
		}
	}
}
void musiquef(Fenetre *f)
{
	
	Mix_Music *musique= Mix_LoadMUS("Kyoukai no Kanata Ending Full.wav");
	Mix_PlayMusic(musique, -1);
	f->delAction(musiquef);
	f->addAction(menu,1);
}
void menutest(Fenetre *f)
{
	if(f->actionsList[menu]==1)
	{
		printf("1\n");
		f->setBG("bgkaw.bmp",100);
		menuTexte=new item(f,"menu",0,0,0,0);
		menuTexte->addApparence("base","Q : Gauche\nD : Droite\nSPACE : Saut simple\nN : accelerer vers le bas\nZ : SUPER SAUT \n(10 secondes entre deux relances)\n\nPour relancer un saut il faut \ntoucher un bloc \nTaper trop vite contre un bloc le fait disparaitre ! \n\n\n\n\nAppuie sur ESPACE pour DEMARRER !\n\n\(Appuie sur A pour QUITTER)","TravelingTypewriter.otf",55,255,255,255,255);
		f->blit(menuTexte);
		f->actionsList[menu]=0;
		printf("1\n");
	}
	while(f->nextEvent()!=0)
	{
		
		if (f->e->type==SDL_KEYDOWN)
		{
			
			printf((f->scanCodeToChar[(f->e->key.keysym.scancode)]).c_str());
			if(f->e->key.keysym.sym==SDLK_SPACE && f->e->key.repeat == 0)
			{
				menuTexte->freeItem();
				f->delAction(menu);
				f->addAction(leerabbit,1);}
			if(f->e->key.keysym.sym==SDLK_9 && f->e->key.repeat == 0)
			{
				f->finMainLoop();
			}
		
		}
	}
}
int main(int argc, char** argv)
{
	printf("1\n");
	Fenetre f((resc-1)*tailleSprite,resl*tailleSprite,"PONG",10,30,2,musiquef,60,1);
	//SDL_SetWindowFullscreen(f.window,SDL_WINDOW_FULLSCREEN_DESKTOP);

	printf("2\n");
	f.mainLoop();
	printf("3\n");
	
	

	
return 0;}
