#/usr/local/Cellar/python/3.7.2_1/Frameworks/Python.framework/Versions/3.7/bin/python3
import os, requests, sys, time
from time import sleep, time
import time
import threading

os.system("clear")
print ("////////////////////////////////////////////////////////////")
print ("///////////////////     2MainKill3r      //////////////////")
print ("//////////////////////////////////////////////////////////\n\n")
print ("Created by Darkside\n")

#list of prosible subdomains
def get_list():
    if len(sys.argv) > 1:
         
        return sys.argv[1]
    else:
        print ("[-] Usage: python3 2MainKill3r.py dictionary.lst\n")
        exit()



#The domain to scan
def get_domain():
    print("[?] Introduce the domain name to attack!")
    data = input()
    if len(data) < 1:
        print ("[-] Wrong input :(\n")
        exit()
    else:
        print ("[+] Scanning...")
        return data



#the TCP connection to test the target.
def tcp_connection(argu, domain):
    with open (argu, "r") as f:
        fname = ("2MainKill-Founds"+time.strftime("%Y%m%d-%H%M%S")+".txt")
        fd = open(fname, "a")
        for line in f:
            query = str("http://"+line.rstrip("\n")+"."+domain+"/")
            query_ssl = str("https://"+line.rstrip("\n")+"."+domain+"/")
            try:
                message = str("[+] Trying "+line.rstrip("\n")+"."+domain+"/ ..................................................................................................\n")
                print (message)

                r = requests.get(query, allow_redirects=True)
                r = requests.get(query_ssl, allow_redirects= True)
            except requests.exceptions.ConnectionError:
                continue

            try:
                print (query+" or "+query_ssl+" exist!\n")
                fd.write(line.strip("\n")+"."+domain+"\n")
            except:
                continue
        fd.close()
        print ("[+] Report saved in "+fname)
        print ("Good bye!!!")
    return

if __name__ == '__main__':

    Get_Arg = get_list()
    Get_Domain = get_domain()
    threads = []

    t = threading.Thread(target=tcp_connection(Get_Arg, Get_Domain))
    threads.append(t)
    t.start()

