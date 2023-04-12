#!/usr/bin/env python3
import sys
import subprocess


def modify_input(input_file, modified_file_name):

    c = 0
    inp = open(input_file, 'r')
    modify_inp = open(modified_file_name, 'w') 
    for line in inp:
        if c==0:
            s = int(line)
        elif c==1:
            p = int(line)
        elif c==2:
            z = int(line)
        else:
            line = line.strip()
            line = line.split()
            line = line[1:]
            line = ' '.join(line)
            modify_inp.write(line+"\n")
        c = c+1
    inp.close()
    modify_inp.close()
    return s,p,z

if __name__=='__main__':

    jar_file_addr = sys.argv[1]
    input_file = sys.argv[2]
    hdfs_input_addr = sys.argv[3]
    hdfs_output_addr = sys.argv[4]
    m_r_addr = sys.argv[5]
    

    modified_file_name = "input_modified.txt"
    s, p, z = modify_input(input_file, modified_file_name)

    reducer_args = "./mapper.py "+str(p)

    cmd1 = ["hdfs", "dfs","-rm", "-r",hdfs_output_addr]
    cmd2 = ["hdfs", "dfs", "-mkdir", hdfs_input_addr]
    cmd3 = ["hdfs", "dfs","-rm", hdfs_input_addr + modified_file_name]
    cmd4 = ["hdfs", "dfs", "-copyFromLocal", modified_file_name, hdfs_input_addr]
    cmd5 = ["hadoop", "jar", jar_file_addr, "-file", m_r_addr+"mapper.py", "-mapper", "python3 mapper.py", "-file", m_r_addr+"reducer.py", "-reducer", "python3 reducer.py "+str(p), "-input", hdfs_input_addr+modified_file_name, "-output", hdfs_output_addr]
    
    subprocess.call(cmd1)
    subprocess.call(cmd2)
    subprocess.call(cmd3)
    subprocess.call(cmd4)
    subprocess.call(cmd5)