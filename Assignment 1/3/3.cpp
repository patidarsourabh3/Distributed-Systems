#include<bits/stdc++.h>
#include <mpi.h>
#define MX 1e7
using namespace std;

void merge(int *keys, int *frequencies, int s, int mid, int e)
{
    int size1 = mid-s+1;
    int size2 = e-mid;
    
    int keys1[size1] = {0};
    int keys2[size2] = {0};
    int frequencies1[size1] = {0};
    int frequencies2[size2] = {0};
    
    int f_keys[size1+size2] = {0};
    int f_frequencies[size1+size2] ={0};

    for(int i=0;i<size1;i++)
    {
        keys1[i] = keys[s+i];
        frequencies1[i] = frequencies[s+i];
    }
    for(int i=0;i<size2;i++)
    {
        keys2[i] = keys[mid+i+1];
        frequencies2[i] = frequencies[mid+i+1];
    }
    int c = 0;
    int i =0, j=0;
    while(i<size1 && j<size2)
    {
        if(keys1[i]<keys2[j])
        {
            f_keys[c] = keys1[i];
            f_frequencies[c] = frequencies1[i];
            i++;
            c++;
        }
        else
        {
            f_keys[c] = keys2[j];
            f_frequencies[c] = frequencies2[j];
            j++;
            c++;
        }
    }
    
    while(i<size1)
    {
        f_keys[c] = keys1[i];
        f_frequencies[c] = frequencies1[i];
        i++;
        c++;
    }
    while(j<size2)
    {
        f_keys[c] = keys2[j];
        f_frequencies[c] = frequencies2[j];
        j++;
        c++;
    }
    
    for(int i=0;i<size1+size2;i++)
    {
        keys[s+i] = f_keys[i];
        frequencies[s+i] = f_frequencies[i];
    }
}


void merge_sort(int *keys, int *frequencies, int s, int e)
{
    if(s>=e)
        return;
    int mid = (s+e)/2;
    merge_sort(keys, frequencies, s, mid);
    merge_sort(keys, frequencies,mid+1, e);
    merge(keys, frequencies,s, mid, e);
    return;
}


vector<int> diagonal_imp(int *frequencies,int *keys,int x, int y,int n,int *roots, int *costs)
{
    if(x==-1 || y==-1)
    {
        return {-1,-1};
    }
    if(x==y)
    {
        return {frequencies[x],x};
    }
    int r = 0;
    int c = MX;
    int s = 0;
    for(int i=x;i<=y;i++)
    {
        s += frequencies[i];
    }
    for(int k=x;k<=y;k++)
    {
        int new_c = s;
        if(k>x)
            new_c += costs[x*(n)+k-1];
        if(k<y)
            new_c += costs[(k+1)*(n)+y];
        if(new_c<c)
        {
            c = new_c;
            r = k; 
        }
    }
    return {c,r};
}

void find_parent(int *roots, int *parent, int l, int r, int par, int pad_size)
{
    if(l<=r)
    {
        parent[roots[l*pad_size+r]] = par;
        find_parent(roots, parent, l, roots[l*pad_size+r]-1, roots[l*pad_size+r], pad_size);
        find_parent(roots, parent, roots[l*pad_size+r]+1, r, roots[l*pad_size+r], pad_size); 
    }
    return;
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

    int n;
    int pad_size;
    int *keys;
    int *frequencies;
    if(rank==0)
    {
        cin>>n;
        pad_size = n;
        pad_size += (comm_size - (n%comm_size));
        keys = new int[pad_size];
        frequencies = new int[pad_size];
        for(int i=0;i<pad_size;i++)
        {
            keys[i] = MX;
            frequencies[i] = -1;
        }
        for(int i=0;i<n;i++)
        {
            cin>>keys[i]>>frequencies[i];
        }
    }
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Bcast(&pad_size, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if(rank!=0)
    {
        keys = new int[pad_size];
        frequencies = new int[pad_size];
    }
    int temp_size = pad_size/comm_size;

    int temp_keys[temp_size] = {0};
    int temp_frequencies[temp_size] = {0};

    MPI_Scatter(keys, temp_size,MPI_INT, temp_keys, temp_size, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(frequencies, temp_size,MPI_INT, temp_frequencies, temp_size, MPI_INT, 0, MPI_COMM_WORLD);
    
    merge_sort(temp_keys, temp_frequencies, 0, temp_size-1);
    
    MPI_Gather(temp_keys, temp_size, MPI_INT, keys, temp_size, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Gather(temp_frequencies, temp_size, MPI_INT, frequencies, temp_size, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);

    if(rank==0)
    {
        int t = 1;
        while(t<comm_size)
        {
            merge(keys, frequencies, 0, (t*temp_size)-1, ((t+1)*temp_size) -1);
            t++;
        }
        // for(int i=0;i<pad_size;i++)
        // {
        //     cout<<"("<<keys[i]<<","<<frequencies[i]<<")"<<" ";
        // }
    }

    MPI_Bcast(keys,pad_size, MPI_INT, 0, MPI_COMM_WORLD);    
    MPI_Bcast(frequencies, pad_size, MPI_INT, 0, MPI_COMM_WORLD);

    int pad_square = pad_size * pad_size;
    int costs[pad_square] = {0};
    int roots[pad_square] = {0};
    
    int t = pad_size+1;
     
    int x_cordinates[pad_size] = {0};
    int y_cordinates[pad_size] = {0};
    int x_cordinates_temp[temp_size]= {0};
    int y_cordinates_temp[temp_size] = {0};

    int itr = 0;
    while(t--)
    {
        if(rank==0)
        {
            for(int j=0;j<pad_size;j++)
            {   
                if(j<pad_size-itr)
                {
                    x_cordinates[j] = j;
                    y_cordinates[j] = itr+j;
                }
                else
                {
                    x_cordinates[j] = -1;
                    y_cordinates[j] = -1;
                }
            }
        }

        MPI_Barrier(MPI_COMM_WORLD);
        int diag[pad_size] = {0};
        int root[pad_size] = {0};
        int diag_temp[temp_size] = {0};
        int root_temp[temp_size] = {0};
        
        MPI_Scatter(x_cordinates, temp_size,MPI_INT, x_cordinates_temp, temp_size, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Scatter(y_cordinates, temp_size,MPI_INT, y_cordinates_temp, temp_size, MPI_INT, 0, MPI_COMM_WORLD);    
        MPI_Scatter(diag, temp_size,MPI_INT, diag_temp, temp_size, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Scatter(root, temp_size,MPI_INT, root_temp, temp_size, MPI_INT, 0, MPI_COMM_WORLD);    

        for(int j=0;j<temp_size;j++)
        {
            vector<int> r_c = diagonal_imp(frequencies, keys, x_cordinates_temp[j], y_cordinates_temp[j], pad_size, roots, costs);
            diag_temp[j] = r_c[0];
            root_temp[j] = r_c[1];
        }
        MPI_Allgather(x_cordinates_temp, temp_size, MPI_INT,x_cordinates,temp_size,MPI_INT,MPI_COMM_WORLD);
        MPI_Allgather(y_cordinates_temp, temp_size, MPI_INT,y_cordinates,temp_size,MPI_INT, MPI_COMM_WORLD);
        MPI_Allgather(diag_temp, temp_size, MPI_INT,diag,temp_size,MPI_INT, MPI_COMM_WORLD);
        MPI_Allgather(root_temp, temp_size, MPI_INT,root,temp_size,MPI_INT, MPI_COMM_WORLD);

    //     if(rank==0)
    //     {
    //         cout<<"Diag : ";
    //         for(int i=0;i<pad_size;i++)
    //         {
    //             cout<<diag[i]<<" ";
    //         }
    //         cout<<endl;
    //     }
       
        for(int i=0;i<pad_size;i++)
        {
            costs[x_cordinates[i]*(pad_size)+y_cordinates[i]] = diag[i];
            roots[x_cordinates[i]*(pad_size)+y_cordinates[i]] = root[i];
        }
        itr++;
    }
    // cout<<"rank "<<rank<<endl;
    MPI_Barrier(MPI_COMM_WORLD);
    if(rank==0)
    {
        // // cout<<"\nCost Array : "<<endl;
        // for(int i=0;i<pad_square;i++)
        // {
        //     if(i%(pad_size) == 0)
        //         cout << endl;
        //     cout<<costs[i]<<"  ";
        // }
        // cout<<"\nRoot Array : "<<endl;
        // for(int i=0;i<pad_square;i++)
        // {
        //     if(i%(pad_size) == 0)
        //         cout << endl;
        //     cout<<roots[i]<<"  ";
        // }
        cout<<costs[n-1]<<endl;
        // cout<<n<<endl;
        int parent[pad_size] = {0};
        find_parent(roots, parent, 0, n-1, -1, pad_size);
        for(int i=0;i<n;i++)
        {
            if(parent[i]==-1)
                cout<<"0"<<" ";
            else    
                cout<<keys[parent[i]]<<" ";
        }
        cout<<endl;
    }
    MPI_Finalize();
    
    return EXIT_SUCCESS;
}