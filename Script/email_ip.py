#!/usr/bin/env python3
import smtplib
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText
from email.mime.base import MIMEBase
from email import encoders
import socket
 
def get_ip():
	s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
	s.connect(("8.8.8.8", 80))
	return s.getsockname()[0]

def email_ip():
	try: 
		ip = get_ip()
		toaddr = ["gurnmc22@wclive.westminster.edu","signap22@wclive.westminster.edu"]
		fromaddr = "wcrobotip@gmail.com"
		passwd = "wcrobots!"
		msg = MIMEMultipart()
		msg['From'] = fromaddr
		msg['To'] = ", ".join(toaddr)
		msg['Subject'] = "Your Robot is ready to connect!"
		body = "Your Robot is ready to connect! the IP address is: "+ip+". To connect to ssh you can use a program like putty on windows, or use the command 'ssh pi@"+ip+"'."
		msg.attach(MIMEText(body, 'plain'))
		server = smtplib.SMTP('smtp.gmail.com',587)
		server.starttls()
		server.login(fromaddr,passwd)	
		text = msg.as_string()
		server.sendmail(fromaddr, toaddr, text)
		server.quit()
	except:
		pass
			
		
if __name__ == '__main__':
    email_ip()
