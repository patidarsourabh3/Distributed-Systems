import sys
import subprocess


def modify_input(input_file, modify_input):
    c = 0
    inp = open(input_file, 'r')
    modify_inp = open(modify_input, 'w') 
    for line in inp:
        if c==0:
            m,n = line.split()
            m = int(m)
            n = int(n)
        elif c<=m:
            line = line.strip()
            line = line.split()
            for i in range(n):
                modify_inp.write("A\t"+str(c-1)+" "+str(i)+" "+line[i]+"\n")
        elif c==m+1:
            p,q = line.split()
            p = int(p)
            q = int(q)
        else:
            line = line.strip()
            line = line.split()
            for i in range(q):
                modify_inp.write("B\t"+str(c-m-2)+" "+str(i)+" "+line[i]+"\n")
        c = c+1
    inp.close()
    modify_inp.close()
    return m, n, q


if __name__=='__main__':

    jar_file_addr = sys.argv[1]
    input_file = sys.argv[2]
    hdfs_input_addr = sys.argv[3]
    hdfs_output_addr = sys.argv[4]
    m_r_addr = sys.argv[5]
    
    modified_file_name = "input_modified.txt"
    m,n,p = modify_input(input_file, modified_file_name)

    mapper_args = "./mapper.py "+str(m)+" "+str(n)+" "+str(p)
    
    cmd1 = ["hdfs", "dfs","-rm", "-r",hdfs_output_addr]
    cmd2 = ["hdfs", "dfs", "-mkdir", hdfs_input_addr]
    cmd3 = ["hdfs", "dfs","-rm", hdfs_input_addr + modified_file_name]
    cmd4 = ["hdfs", "dfs", "-copyFromLocal", modified_file_name, hdfs_input_addr]
    cmd5 = ["hadoop", "jar", jar_file_addr, "-file", m_r_addr+"mapper.py", "-mapper", mapper_args, "-file", m_r_addr+"reducer.py", "-reducer", "./reducer.py", "-input", hdfs_input_addr+modified_file_name, "-output", hdfs_output_addr]
    
    subprocess.call(cmd1)
    subprocess.call(cmd2)
    subprocess.call(cmd3)
    subprocess.call(cmd4)
    subprocess.call(cmd5)