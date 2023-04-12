#include<bits/stdc++.h>
#include<mpi.h>
using namespace std;

int x_y_count(vector<int> curr_x, vector<int> curr_y, int a, int b, int idx)
{
    int c = 1;
    int new_idx=0;
    for(int i=idx+1;i<curr_x.size();i++)
    {
        if(curr_x[i]==a && curr_y[i]==b)
        {
            c++;
            new_idx = i;
        }
    }
    if(c==2)
        return new_idx;
    return -1;
}

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);
    int comm_size;
	MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
	if(comm_size <1 || comm_size >12)
	{
		cout<<"This application must be run within range of 1-12 processes"<<endl;
		MPI_Abort(MPI_COMM_WORLD, -1);
	}
    int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);   
    int n,m,k,t;
    vector<int> x;
    vector<int> y;
    vector<char> d;
    if(rank==0)
    {
        cin>>n>>m>>k>>t;
        x = vector<int>(k,0);
        y = vector<int>(k,0);
        d = vector<char>(k);
        for(int i=0;i<k;i++)
        {
            cin>>x[i]>>y[i]>>d[i];
        }
    }
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&k, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&t, 1, MPI_INT, 0, MPI_COMM_WORLD);

    vector<int> up_x, up_y, down_x, down_y, curr_x, curr_y, same_x, same_y;
    vector<char> up_d, down_d, curr_d, same_d;

    if(rank!=0)
    {
        x = vector<int>(k,0);
        y = vector<int>(k,0);
        d = vector<char>(k);
    }
    MPI_Bcast(x.data(), k,MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(y.data(), k,MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(d.data(), k,MPI_CHAR, 0, MPI_COMM_WORLD);

    int sz = m/comm_size;
    // cout<<"Size : "<<sz<<endl;
    for(int i=0;i<k;i++)
    {
        if(y[i]>=rank*sz && y[i]<(rank+1)*sz)
        {
            curr_x.push_back(x[i]);
            curr_y.push_back(y[i]);
            curr_d.push_back(d[i]);
        }
        else if(y[i]>=rank*sz && rank == comm_size-1)
        {
            curr_x.push_back(x[i]);
            curr_y.push_back(y[i]);
            curr_d.push_back(d[i]);
        }
    }

    
    while(t--)
    {
        for(int i=0;i<curr_x.size();i++)
        {
            if(curr_d[i]=='L')
            {
                if(curr_x[i]!=0)
                {
                    same_x.push_back(curr_x[i]-1);
                    same_y.push_back(curr_y[i]);
                    same_d.push_back(curr_d[i]);      
                }
                else
                {
                    same_x.push_back(curr_x[i]+1);
                    same_y.push_back(curr_y[i]);
                    same_d.push_back('R');
                }
            }
            else if(curr_d[i]=='R')
            {
                if(curr_x[i]!=n-1)
                {
                    same_x.push_back(curr_x[i]+1);
                    same_y.push_back(curr_y[i]);
                    same_d.push_back(curr_d[i]);      
                }
                else
                {
                    same_x.push_back(curr_x[i]-1);
                    same_y.push_back(curr_y[i]);
                    same_d.push_back('L');
                }
            }
            else if(curr_d[i]=='U')
            {
                if(curr_y[i]!=m-1)
                {
                    curr_y[i] +=1;
                    if(curr_y[i]>=rank*sz && curr_y[i]<(rank+1)*sz)
                    {
                        same_x.push_back(curr_x[i]);
                        same_y.push_back(curr_y[i]);
                        same_d.push_back(curr_d[i]);
                    }
                    else if(curr_y[i]>=rank*sz && rank == comm_size-1)
                    {
                        same_x.push_back(curr_x[i]);
                        same_y.push_back(curr_y[i]);
                        same_d.push_back(curr_d[i]);
                    }
                    else
                    {
                        up_x.push_back(curr_x[i]);
                        up_y.push_back(curr_y[i]);
                        up_d.push_back('U');
                    }
                }
                else
                {
                    curr_y[i] -=1;
                    if(curr_y[i]>=rank*sz && curr_y[i]<(rank+1)*sz)
                    {
                        same_x.push_back(curr_x[i]);
                        same_y.push_back(curr_y[i]);
                        same_d.push_back('D');
                    }
                    else if(curr_y[i]>=rank*sz && rank == comm_size-1)
                    {
                        same_x.push_back(curr_x[i]);
                        same_y.push_back(curr_y[i]);
                        same_d.push_back('D');
                    }
                    else
                    {
                        down_x.push_back(curr_x[i]);
                        down_y.push_back(curr_y[i]);
                        down_d.push_back('D');
                    }
                }
            }
            else if(curr_d[i]=='D')
            {
                if(curr_y[i]!=0)
                {
                    curr_y[i] -=1;
                    if(curr_y[i]>=rank*sz && curr_y[i]<(rank+1)*sz)
                    {
                        same_x.push_back(curr_x[i]);
                        same_y.push_back(curr_y[i]);
                        same_d.push_back(curr_d[i]);
                    }
                    else if(curr_y[i]>=rank*sz && rank == comm_size-1)
                    {
                        same_x.push_back(curr_x[i]);
                        same_y.push_back(curr_y[i]);
                        same_d.push_back(curr_d[i]);
                    }
                    else
                    {
                        down_x.push_back(curr_x[i]);
                        down_y.push_back(curr_y[i]);
                        down_d.push_back(curr_d[i]);
                    }
                }
                else
                {
                    curr_y[i] +=1;
                    if(curr_y[i]>=rank*sz && curr_y[i]<(rank+1)*sz)
                    {
                        same_x.push_back(curr_x[i]);
                        same_y.push_back(curr_y[i]);
                        same_d.push_back('U');
                    }
                    else if(curr_y[i]>=rank*sz && rank == comm_size-1)
                    {
                        same_x.push_back(curr_x[i]);
                        same_y.push_back(curr_y[i]);
                        same_d.push_back('U');
                    }
                    else
                    {
                        up_x.push_back(curr_x[i]);
                        up_y.push_back(curr_y[i]);
                        up_d.push_back('U');
                    }
                }
            }
        }
        int up_size = up_x.size();
        int up_size_temp=0;
        if(rank!=comm_size-1)
        {
            MPI_Send(&up_size, 1, MPI_INT, rank+1, 0, MPI_COMM_WORLD);
            MPI_Send(up_x.data(), up_size, MPI_INT, rank+1, 0, MPI_COMM_WORLD);
            MPI_Send(up_y.data(), up_size, MPI_INT, rank+1, 0, MPI_COMM_WORLD);
            MPI_Send(up_d.data(), up_size, MPI_CHAR, rank+1, 0, MPI_COMM_WORLD);
        }
        if(rank!=0)
        {
            MPI_Recv(&up_size_temp, 1, MPI_INT, rank-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            vector<int> up_x_temp(up_size_temp, 0);
            vector<int> up_y_temp(up_size_temp, 0);
            vector<char> up_d_temp(up_size_temp);
            MPI_Recv(up_x_temp.data(), up_size_temp, MPI_INT, rank-1, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            MPI_Recv(up_y_temp.data(), up_size_temp, MPI_INT, rank-1, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            MPI_Recv(up_d_temp.data(), up_size_temp, MPI_CHAR, rank-1, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            for(int i=0;i<up_size_temp;i++)
            {
                same_x.push_back(up_x_temp[i]);
                same_y.push_back(up_y_temp[i]);
                same_d.push_back(up_d_temp[i]);
            }
        }
        int down_size = down_x.size();
        int down_size_temp=0;
        if(rank!=0)
        {
            MPI_Send(&down_size, 1, MPI_INT, rank-1, 0, MPI_COMM_WORLD);
            // cout<<"Rank & up size "<<rank<<" "<<up_size<<endl;
            MPI_Send(down_x.data(), down_size, MPI_INT, rank-1, 0, MPI_COMM_WORLD);
            MPI_Send(down_y.data(), down_size, MPI_INT, rank-1, 0, MPI_COMM_WORLD);
            MPI_Send(down_d.data(), down_size, MPI_CHAR, rank-1, 0, MPI_COMM_WORLD);
        }
        if(rank!=comm_size-1)
        {
            MPI_Recv(&down_size_temp, 1, MPI_INT, rank+1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            vector<int> down_x_temp(down_size_temp, 0);
            vector<int> down_y_temp(down_size_temp, 0);
            vector<char> down_d_temp(down_size_temp);
            MPI_Recv(down_x_temp.data(), down_size_temp, MPI_INT, rank+1, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            MPI_Recv(down_y_temp.data(), down_size_temp, MPI_INT, rank+1, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            MPI_Recv(down_d_temp.data(), down_size_temp, MPI_CHAR, rank+1, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
           
            for(int i=0;i<down_size_temp;i++)
            {
                same_x.push_back(down_x_temp[i]);
                same_y.push_back(down_y_temp[i]);
                same_d.push_back(down_d_temp[i]);
            }
        }
        curr_x.clear();
        curr_y.clear();
        curr_d.clear();
        curr_x = same_x;
        curr_y = same_y;
        curr_d = same_d;

        same_x.clear();
        same_y.clear();
        same_d.clear();
        up_x.clear();
        up_y.clear();
        up_d.clear();
        down_x.clear();
        down_y.clear();
        down_d.clear();

        if(t!=0)
        {
            for(int i=0;i<curr_x.size();i++)
            {
                int idx = x_y_count(curr_x, curr_y, curr_x[i], curr_y[i], i);
                if(idx!=-1)
                {
                    if((curr_d[i]=='R' && curr_d[idx]=='L') ||(curr_d[i]=='L' && curr_d[idx]=='R'))
                    {
                        curr_d[i] = 'U';
                        curr_d[idx] = 'D';
                    }
                    else if((curr_d[i]=='U' && curr_d[idx]=='D') ||(curr_d[i]=='D' && curr_d[idx]=='U'))
                    {
                        curr_d[i] = 'L';
                        curr_d[idx] = 'R';
                    }
                }
            }
        }
    }

    MPI_Barrier(MPI_COMM_WORLD);
    int cur_size = curr_x.size();
    if(rank!=0)
    {
       MPI_Send(&cur_size, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);     
    }
    int dis[comm_size]={0};
    int chunk[comm_size] = {0};
    
    if(rank==0)
    {
        int cur_size_temp;
        dis[0] = 0;
        chunk[0] = cur_size;
        // cout<<"Chunk Size : "<< cur_size<<endl;
        for(int i=1;i<comm_size;i++)
        {
            MPI_Recv(&cur_size_temp, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            chunk[i] = cur_size_temp;
        }
        for(int i=1;i<comm_size;i++)
        {
            dis[i] =dis[i-1] +chunk[i-1];
        }
    }

    vector<int> ans_x(k);
    vector<int> ans_y(k);
    vector<char> ans_d(k);

    MPI_Gatherv(curr_x.data(), cur_size, MPI_INT,ans_x.data(),chunk,dis,MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Gatherv(curr_y.data(), cur_size, MPI_INT,ans_y.data(),chunk,dis,MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Gatherv(curr_d.data(), cur_size, MPI_CHAR,ans_d.data(),chunk,dis,MPI_CHAR, 0, MPI_COMM_WORLD);
    
    if(rank==0)
    {
        // cout<<"Answer :"<<endl;
        vector<pair<pair<int,int>,char>> v;
        for(int i=0;i<k;i++)
        {
            v.push_back({{ans_x[i], ans_y[i]}, ans_d[i]});
        }
        sort(v.begin(), v.end());
        for(auto i:v)
        {
            cout<<i.first.first<<" "<<i.first.second<<" "<<i.second<<endl;
        }
    }
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
}