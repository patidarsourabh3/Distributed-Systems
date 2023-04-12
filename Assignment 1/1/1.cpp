#include <bits/stdc++.h>
#include <mpi.h>

using namespace std;

bool check(double a, double b, int k)
{
    double x = 0;
    double y = 0;
    double new_x;
    double new_y;
    while(k--)
    {
        new_x = x*x - y*y + a;
        new_y = 2*x*y + b;
        if(sqrt(new_x*new_x + new_y * new_y)> 2.0)
            return false;
        x = new_x;
        y = new_y;   
    }
    return true;
}

int main(int argc, char* argv[])
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
    int n, m, k;
    vector<double> vec_x, vec_y;
    vector<int> final_res;
    if(rank == 0)
    {
        cin>>n>>m>>k;

        double x1 = -1.5, x2 = 1;
        double y1 = -1, y2 = 1;
        double dx = abs(((x1-x2)*1.0))/(n-1);
        double dy = abs(((y2-y1)*1.0))/(m-1);
        vec_x = vector<double>(n,0);
        vec_y = vector<double>(m,0);
        for(int i=0;i<vec_x.size();i++)
        {
            vec_x[i] = x1+i*dx;
        }
        for(int i=0;i<vec_y.size();i++)
        {
            vec_y[i] = y1+i*dy;
        }
    }
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Bcast(&k, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);
    if(rank!=0)
    {
        vec_x = vector<double>(n,0);
        vec_y = vector<double>(m,0);    
    }
    MPI_Bcast(vec_y.data(), vec_y.size(), MPI_DOUBLE, 0, MPI_COMM_WORLD);
    if(n%comm_size!=0)
    {
        int pad = comm_size - (n%comm_size);
        while(pad--)
            vec_x.push_back(0);
    }
    MPI_Barrier(MPI_COMM_WORLD);
    int temp_x = vec_x.size()/comm_size;
    vector<int> vec_x_index(vec_x.size(), 0);
    for(int i=0;i<vec_x.size();i++)
        vec_x_index[i] = i;
    vector<double> partial_vec_x(temp_x, 0);
    vector<int> partial_vec_x_index(temp_x, 0);
    
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Scatter(vec_x.data(), temp_x, MPI_DOUBLE, partial_vec_x.data(), temp_x, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Scatter(vec_x_index.data(), temp_x, MPI_INT, partial_vec_x_index.data(), temp_x, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);

    vector<int> res(m*temp_x*3,0);
    int c = 0;
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<temp_x;j++)
        {
            res[c] = partial_vec_x_index[j];
            res[c+1] = i;
            if(check(partial_vec_x[j], vec_y[i], k))
            {
                res[c+2] = 1;
            }
            c = c+3;
        }
    }
    if(rank==0)
    {
        final_res = vector<int>(vec_x.size()*m*3,0);
    }
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Gather(res.data(), m*temp_x*3, MPI_INT, final_res.data(), m*temp_x*3, MPI_INT, 0, MPI_COMM_WORLD);
    
    if(rank==0)
    {
        vector<vector<int>> ans(m, vector<int>(n,0));
        for(int i=0;i<final_res.size();i=i+3)
        {
            if(final_res[i+2]==1)
            {
                int x = final_res[i];
                int y = final_res[i+1];
                if(x<m && y<n)
                    ans[y][x] = 1;
            }
        }
        for(int i=0;i<ans.size();i++)
        {
            for(int j=0;j<ans[0].size();j++)
            {
                cout<<ans[i][j]<<" ";
            }
            cout<<endl;
        }
    }
    MPI_Finalize();    
    return EXIT_SUCCESS;
}