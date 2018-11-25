#include <iostream>
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
using namespace std;
//using namespace std;

#define MAXFNAME	14
#define BLKSIZE		512
char *devfiles[] = {"TEST",NULL};
int devfd[] = {-1, -1};


// Data structure definitions
struct SupBlock {
	char sb_vname[MAXFNAME];
	int	sb_nino;
	int	sb_nblk;
	int	sb_nrootdir;
	int	sb_nfreeblk;
	int	sb_nfreeino;
	int	sb_flags;
	unsigned short sb_freeblks[BLKSIZE/sizeof(unsigned short)];
	int	sb_freeblkindex;
	int	sb_freeinoindex;	
	unsigned int	sb_chktime;
	unsigned int	sb_ctime;
	unsigned short sb_freeinos[(BLKSIZE - (54))/2];
};

struct OnDiskDirEntry {
	char	* d_name;
	unsigned short	d_ino;
};

struct DirEntry {
	struct OnDiskDirEntry d_entry;
	int	d_offset;
	int d_flag;
	struct DirEntry *d_next;
}; 
struct InCoreINode *inodetable;
struct DirEntry dtable[10];
int inodelist[100];
int freeblock[8000];
#define ROOTDIRSIZE	((4 * 512)/sizeof(struct OnDiskDirEntry))

struct INode {
	unsigned int	i_size;
	unsigned int	i_atime;
	unsigned int	i_ctime;
	unsigned int	i_mtime;
	unsigned short	i_blks[13];
	short		i_mode;
	unsigned int	i_uid;
	unsigned int	i_gid;
	unsigned int	i_gen;
	unsigned int	i_lnk;
};

#define INODETABSIZE	((16 * 512) / sizeof(struct INode))

struct InCoreINode {
	struct INode 	ic_inode;
	int 		ic_ref;
	int		ic_ino;
	short		ic_dev;
	struct DirEntry * ic_d;
	struct InCoreINode	*ic_next;
	struct InCoreINode	*ic_prev;
	
};


struct OpenFileObject {
	struct InCoreINode	*ofo_inode;
	int			ofo_mode;
	unsigned int		ofo_curpos;
	int			ofo_ref;
	OpenFileObject *ofo_next;
}*ofo;

//============= TESTING APPLICATION USING THESE FS CALLS ==============

// Menu driven testing application for creation of fs, 
// and all file and directory related operations
int main()
{
}

//============= SYSTEM CALL LEVEL NOT FOLLOWED =======

//============= VNODE/VFS NOT FOLLOWED ===============

//============== UFS INTERFACE LAYER ==========================
int MkFS(int dev, int ninodes, int nrootdir, int blksize)
{
	int rootentrycount = ROOTDIRSIZE;
	int inodecount = INODETABSIZE;
	int blkcount = 8192;
	char buf[512];
	struct SupBlock sb;
	int reservblks = 1 + 2 + 8 + 4; // boot, super, inodetable, rootdir blks

	// Assuming only predefined sizes are used
	// Otherwise we have to recompute according to the parameters given.
	//
	
	// Boot block dummy block (Because no boot loader nothing...)
	bzero(buf, 512);
	write(devfd[dev], buf, 512);	
	
	// Write initialized superblock
	strcpy(sb.sb_vname, "TESTFILESYS");
	sb.sb_nino = inodecount;
	sb.sb_nblk = blkcount;
	sb.sb_nrootdir = rootentrycount;
	sb.sb_nfreeblk = blkcount - reservblks;
	sb.sb_nfreeino = inodecount;
	sb.sb_flags =0;
	// initialize free bl;ock list
	//unsigned short sb_freeblks[BLKSIZE/sizeof(unsigned short)];
	sb.sb_freeblkindex = (BLKSIZE/sizeof(unsigned short))-1;
	sb.sb_freeinoindex = (BLKSIZE - (54))/2 - 1;	
	sb.sb_chktime = 0;
	sb.sb_ctime = 0;
	// initialize free inodelist
	//unsigned short sb_freeinos[(BLKSIZE - (54))/2];

	
	


	// Write initialized list of inodes
		inodetable=NULL;
		ofo=NULL;
	
	// Write initialized list of directory entries
	
	
	// Fill the remaining empty datablocks
	int i;
	for(i=17;i<8000;i++)
	freeblock[i]=-1;
	// Write free blk information (data structures)
	for(i=3;i<100;i++)
	inodelist[i]=-1;
	}

// Open/create a file in the given directory with specified uid, gid 
// and attributes. Type of modes are limited to read, write and append only.
int OpenFile(int dirhandle, char fname[], int mode, int uid, int gid, int attrib)
{int fd;
   // struct INode in;
   OpenFileObject *old=ofo;
   if(ofo==NULL)
                                      { 
                                          ofo=new OpenFileObject();
                                       ofo->ofo_next=NULL;
                                       ofo->ofo_mode=attrib;
                                       }
                                       else{
                                            while(ofo->ofo_next!=NULL)
                                            ofo=ofo->ofo_next;
                                            ofo->ofo_next=new OpenFileObject();
                                            ofo->ofo_mode=attrib;
                                            ofo->ofo_next->ofo_next=NULL;
                                            }
    
    if(inodetable!=NULL)
    {
                      struct  InCoreINode *t=inodetable;
    while(t!=NULL)
   {
                  if(t->ic_ino==dirhandle)
                  break;
                   t=t->ic_next;
                   }
                   if(t!=NULL)
                   {
                              struct DirEntry *x=t->ic_d;
                    while(x!=NULL)
                    {
                                        if(x->d_entry.d_name==fname)
                                        break;
                                        x=x->d_next;
                                        }
                   if(x!=NULL)
                   { 
                              int k=x->d_entry.d_ino;
                              InCoreINode *b=inodetable;
                              
                              while(b!=NULL)
                              {
                                            if(b->ic_ino==k)
                                            break;
                                            b=b->ic_next;
                                            }
                                            
                                            
                              lseek(devfd[0], (t->ic_inode.i_blks[0])* BLKSIZE, SEEK_SET);
                   ofo->ofo_inode=b;
                   ofo=old;
                    return x->d_entry.d_ino;
                   }
                              
                   else
                       { 
                        struct InCoreINode *r=inodetable;
                        while(inodetable->ic_next!=NULL)
                        inodetable=inodetable->ic_next;
                        struct InCoreINode *e= new InCoreINode();
                        e->ic_prev=inodetable;
                        e->ic_next=NULL;
                        inodetable->ic_next=e;
                        
                        int j;
                        for(j=3;j<100;j++)
                       { if(inodelist[j]==-1)
                       {inodelist[j]=j;
                       break;}
                       }
                       int count=0;
                       fd=j;
                       inodetable->ic_next->ic_ino=j;
                       for(j=17;j<8000;j++)
                       {
                                           if(freeblock[j]==-1)
                                          {
                                                               inodetable->ic_next->ic_inode.i_blks[count]=j;
                                                               freeblock[j]=1;
                                                                count++;
                                                                }
                                                                
                                                                if(count==10)
                                                                break;
                                                                }
                                                           inodetable->ic_next->ic_inode.i_uid=uid;
                                                           inodetable->ic_next->ic_inode.i_gid=gid;
                                                           inodetable->ic_next->ic_inode.i_mode=attrib;
                                                           ofo->ofo_inode=inodetable->ic_next;
                                                           ofo=old;
                     lseek(devfd[0], (inodetable->ic_next->ic_inode.i_blks[0])* BLKSIZE, SEEK_SET);
                                                           
                                                                count=0;
                                                                
                        inodetable=r;
                       
                       
                       
                              struct InCoreINode *u=inodetable;
                        while(inodetable!=NULL)
                        {
                                      if(inodetable->ic_ino==dirhandle)
                                      break;
                                      inodetable=inodetable->ic_next;
                                      }
                                      if(inodetable==NULL)
                                      {
                                                          cout<<"NO DIR";//printf("No such directory");
                                                          return -1;}
                                  struct DirEntry *s=inodetable->ic_d;
                                  while(inodetable->ic_d->d_next!=NULL)
                                  inodetable->ic_d=inodetable->ic_d->d_next;
                                  struct DirEntry *c=new DirEntry();
                                  c->d_entry.d_name=fname;
                                  c->d_flag=1;
                                  c->d_entry.d_ino=fd;
                                  inodetable->ic_d->d_next=c;
                                  inodetable->ic_d->d_next->d_next=NULL;
                                    inodetable->ic_d=s;  
                                    inodetable=u;
                                    return fd;
                                    }
                                    }
                                    }
                                       
                        return fd;
                                    }
                  
// Close a file
int CloseFile(int fhandle)
{
    OpenFileObject *old2,*old1=ofo;
    old2=NULL;
    while(ofo!=NULL)
    {
                    if(ofo->ofo_inode->ic_ino==fhandle)
                    break;
                    old2=ofo;
                    ofo=ofo->ofo_next;
                    }
                    if(ofo==NULL)
                    return -1;
                    if(ofo==old2)
                    ofo=NULL;
                    else
                   {
                   
                         old2->ofo_next=ofo->ofo_next;
                         ofo=old1;
                         }
                    
                   
    return 0;
}

// Read from a file already opened, nbytes into buf
int ReadFile(int fhandle, char buf[], int nbytes)
{
    OpenFileObject *old3=ofo;
    while(old3!=NULL)
    {
                     if(old3->ofo_inode->ic_ino==fhandle)
                     break;
                     old3=old3->ofo_next;
                     }
                     if(old3==NULL)
                     {
                                   cout<<"Error in reading file"<<endl;
                                   return -1;
                                   }
       lseek(devfd[0],(old3->ofo_inode->ic_inode.i_blks[0])*BLKSIZE,SEEK_SET);
      int h= read(devfd[0],buf,nbytes);
      lseek(devfd[0],h,SEEK_CUR);
      old3->ofo_curpos=(old3->ofo_inode->ic_inode.i_blks[0])*BLKSIZE +h;
       return h;
    
}

// Write into a file already opened, nbytes from buf
int WriteFile(int fhandle, char buf[], int nbytes)
{
    OpenFileObject *old3=ofo;
    while(old3!=NULL)
    {
                     if(old3->ofo_inode->ic_ino==fhandle)
                     break;
                     old3=old3->ofo_next;
                     }
                     if(old3==NULL)
                     {
                                   cout<<"Error in writing file"<<endl;
                                   return -1;
                                   }
       lseek(devfd[0],(old3->ofo_inode->ic_inode.i_blks[0])*BLKSIZE,SEEK_SET);
      int h= write(devfd[0],buf,nbytes);
      
      lseek(devfd[0],h,SEEK_CUR);
      old3->ofo_curpos=(old3->ofo_inode->ic_inode.i_blks[0])*BLKSIZE +h;
       return h;
    }

// Move the file pointer to required position
int SeekFile(int fhandle, int pos, int whence)
{
    OpenFileObject *old3=ofo;
    while(old3!=NULL)
    {
                     if(old3->ofo_inode->ic_ino==fhandle)
                     break;
                     old3=old3->ofo_next;
                     }
                     if(old3==NULL)
                     {
                                   cout<<"Error in seeking file"<<endl;
                                   return -1;
                                   }
       lseek(devfd[0],(old3->ofo_inode->ic_inode.i_blks[0])*BLKSIZE,SEEK_SET);
       if(whence==SEEK_SET)
       lseek(devfd[0],pos,SEEK_CUR);
       if(whence==SEEK_CUR)
       lseek(devfd[0],(old3->ofo_curpos)+pos,SEEK_CUR);
      
       return 1;
    
}

// Create a directory
int MkDir(int pardir, char *dname, int uid, int gid, int attrib)
{
    
    InCoreINode * sd=inodetable;
    while(inodetable->ic_next!=NULL)
    inodetable=inodetable->ic_next;
    InCoreINode *w=new InCoreINode();
    w->ic_inode.i_uid=uid;
    w->ic_inode.i_gid=gid;
     int j;
     for(j=3;j<100;j++)
           { if(inodelist[j]==-1)
              {
              inodelist[j]=j;
                  break;
                  }
            }
            int fd1=j;
            w->ic_ino=j;
            w->ic_inode.i_mode=attrib;
            inodetable->ic_next=w;
            inodetable->ic_next->ic_prev=inodetable;
            inodetable->ic_next->ic_next=NULL;
            inodetable=sd;
    InCoreINode *ed=inodetable;
    if(pardir==-1)
    {
                  dtable[0].d_entry.d_ino=fd1;
                  dtable[0].d_entry.d_name=dname;
                  dtable[0].d_next=NULL;
                  }
                  else{
    while(ed!=NULL)
    {
                   if(ed->ic_ino==pardir)
                   break;
                   ed=ed->ic_next;
                   }
                 DirEntry *g=ed->ic_d;
                 while(ed->ic_d->d_next!=NULL)
                 ed->ic_d=ed->ic_d->d_next;
                 ed->ic_d->d_next=new DirEntry();
                 ed->ic_d->d_next->d_next=NULL;
                 ed->ic_d->d_next->d_entry.d_ino=fd1;
                 ed->ic_d->d_next->d_entry.d_name=dname;
                 ed->ic_d=g;
                 }
                 return fd1;
                   
                 }

// Delete directory (if itis empty)
int RmDir(int pardir, char *dname)
{int x;
    if(pardir==-1)
    {
     x=dtable[0].d_entry.d_ino;
    dtable[0].d_entry.d_ino=0;
    InCoreINode *r=inodetable;
    while(inodetable!=NULL)
    {
                           if(inodetable->ic_ino==x)
                           break;
                           inodetable=inodetable->ic_next;
                           }
                            if(inodetable->ic_prev==inodetable->ic_next)
                          { inodetable=NULL;return 0;}
                           if(inodetable->ic_prev!=NULL)
                           inodetable->ic_prev->ic_next=inodetable->ic_next;
                           if(inodetable->ic_next!=NULL)
                           inodetable->ic_next->ic_prev=inodetable->ic_prev;
                           inodetable=r;
                           }
                           else
                           {
                               InCoreINode *r1=inodetable;
                               while(r1!=NULL)
                               {
                                              if(r1->ic_ino==pardir)
                                              break;
                                              r1=r1->ic_next;
                                              }
                                              DirEntry *old4=NULL,*rt=r1->ic_d;
                                              while(rt!=NULL)
                                              {
                                                             if(rt->d_entry.d_name==dname)
                                                             break;
                                                             old4=rt;
                                                             rt=rt->d_next;
                                                             }
                               x=rt->d_entry.d_ino;
                               if(old4!=NULL)
                               old4->d_next=rt->d_next;
                              else if(old4==rt)
                               r1->ic_d=NULL;
                               InCoreINode *r=inodetable;
                        while(inodetable!=NULL)
                         {
                           if(inodetable->ic_ino==x)
                           break;
                           inodetable=inodetable->ic_next;
                           }
                           if(inodetable->ic_prev==inodetable->ic_next)
                          { inodetable=NULL;return 0;}
                           if(inodetable->ic_prev!=NULL)
                           inodetable->ic_prev->ic_next=inodetable->ic_next;
                           if(inodetable->ic_next!=NULL)
                           inodetable->ic_next->ic_prev=inodetable->ic_prev;
                           
                           inodetable=r;
                           }
                         return 0;         
                      }

int OpenDir(int pardir, char *dname)
{
 OpenFileObject *old3=ofo;
    while(old3!=NULL)
    {
                     if(old3->ofo_inode->ic_ino==pardir)
                     break;
                     old3=old3->ofo_next;
                     }
                     if(old3==NULL)
                     {
                                   cout<<"Error in opening dir "<<endl;
                                   return -1;
                     }
                    DirEntry *yu= old3->ofo_inode->ic_d;
                    while(yu!=NULL)
                    {
                                   if(yu->d_entry.d_name==dname)
                                   break;
                                   yu=yu->d_next;
                                   }
    OpenFileObject *old6=ofo;
    while(old6->ofo_next!=NULL)
    {
                     old6=old6->ofo_next;
                     }
                     old6->ofo_next=new OpenFileObject();
                     old6->ofo_next->ofo_next=NULL;
                     old6->ofo_inode=old3->ofo_inode;
    return 0;   
    
}

int CloseDir(int dirhandle)
{
   OpenFileObject *old2,*old1=ofo;
    old2=NULL;
    while(ofo!=NULL)
    {
                    if(ofo->ofo_inode->ic_ino==dirhandle)
                    break;
                    old2=ofo;
                    ofo=ofo->ofo_next;
                    }
                    if(ofo==NULL)
                    return -1;
                    if(ofo==old2)
                    ofo=NULL;
                    else
                   {
                   
                         old2->ofo_next=ofo->ofo_next;
                         ofo=old1;
                         }
                    
                   
    return 0; 
}

int SeekDir(int dirhandle, int pos, int whence)
{
}

int ReadDir(int dirhandle, struct DirEntry *dent)
{
}
int WriteDir(int dirhandle, struct DirEntry *dent)
{
}

//============== UFS INTERNAL LOW LEVEL ALGORITHMS =============
int ReadInode(int dev, int ino, struct INode *inode)
{
  InCoreINode *r=inodetable;
  while(r!=NULL)
  {
                if(r->ic_ino==ino)
                break;
                r=r->ic_next;
                }
                if(r==NULL)
                return -1;
                inode=&(r->ic_inode);
                
                return 0; 
}

int WriteInode(int dev, int ino, struct INode *inode)
{
    InCoreINode *r=inodetable;
  while(r!=NULL)
  {
                if(r->ic_ino==ino)
                break;
                r=r->ic_next;
                }
                if(r==NULL)
                return -1;
                (r->ic_inode)=*inode;
                return 0; 
}

int AllocInode(int dev)
{
   InCoreINode *r=inodetable;
   while(r->ic_next!=NULL)
   r=r->ic_next;
   r->ic_next=new InCoreINode();
   r->ic_next->ic_next=NULL;
   r->ic_next->ic_ino=r->ic_ino+1;
   r->ic_next->ic_prev=r;
   r->ic_next->ic_dev=dev;
   return 0;
   
}
int FreeInode(int dev, int ino)
{
    InCoreINode *r=inodetable;
    while(r!=NULL)
    {
                           if(r->ic_ino==ino)
                           break;
                           r=r->ic_next;
                           }
                           if(r!=NULL)
                           {
                           if(r->ic_prev!=NULL)
                           r->ic_prev->ic_next=r->ic_next;
                           if(r->ic_next!=NULL)
                           r->ic_next->ic_prev=r->ic_prev;
                           return 0;
                           }
                           return -1;
                           }

int AllocBlk(int dev)
{int i;
  for( i=17;i<8000;i++)
  if(freeblock[i]==-1)
  {freeblock[i]=i;
  break;
}
return i; 
}

int FreeBlk(int dev, int blk)
{
    freeblock[blk]=-1;
    return blk;
}

//============== DEVICE DRIVER LEVEL =====================

// Reading a logical block blk from device dev
int ReadBlock(int dev, int blk, int buf[BLKSIZE])
{
	// Check for validity of the block
	// Check for validity of the device

	// If OK read the block
	lseek(devfd[dev], blk * BLKSIZE, SEEK_SET);
	return read(devfd[dev], buf, BLKSIZE);
}

// Writing a logical block blk to device dev
int WriteBlock(int dev, int blk)
{
	// Check for validity of the block
	// Check for validity of the device

	// If OK write the block
char *buf;
	lseek(devfd[dev], blk * BLKSIZE, SEEK_SET);
	return write(devfd[dev], buf, BLKSIZE);
}


// Open the device
int OpenDevice(int dev)
{
	// Open the device related file for both reading and writing.
	//
	if ((devfd[dev] = open(devfiles[dev], O_RDWR)) < 0)
	{
		cout<<"Opening device file failure:";
		exit(0);
	}
	return devfd[dev];
}

// Shutdown the device
int ShutdownDevice(int dev)
{
	// if (dev < ... && dev > ...)
	if (devfd[dev] >= 0)
		close(devfd[dev]);

	return 0;
}

