'use client'
import '../styles/globals.css'
import { Inter, Poppins, Signika } from 'next/font/google'
import { createNewWs, sendMsg } from './websocket'
import { useGlobalState } from './globals';
import { useEffect } from 'react';
import { useRouter, usePathname } from 'next/navigation';

const inter = Inter({ subsets: ['latin'] });
const poppins = Poppins({ subsets: ['latin'], weight: ['500', '800'] });
const signika = Signika({ subsets: ['latin'], weight: ['500', '600'] });

const loginCode = process.env.LOGIN_CODE;

export const metadata = {
  title: 'Taki online',
  description: 'Arad & Ron',
}

function disableF5(event : any)
{
  if ((event.which || event.keyCode) === 116) event.preventDefault();
}

export default function RootLayout({
  children,
}: {
  children: React.ReactNode
}) {
  const router = useRouter();
  const pathName = usePathname();
  const [global_username, setUsername] = useGlobalState("username");
  const [global_password, setPass] = useGlobalState("password");

  useEffect(() => 
  {
    try
    {
      createNewWs();
      if (global_username != '' && global_password != '')
      {
        sendMsg(loginCode!.charAt(0), `"username":"${global_username}", "password":"${global_password}"` ).then((response) => 
        {

        }).catch((error) => {});
      } 
    }
    catch (e)
    {
      console.log('Server closed')
    }
    
  }, []);

  useEffect(() => {
    
    if (global_username == '' && pathName != '/signup')
    {
      router.push('/login')
    } 
  }, [global_username]);

  return (
    <html lang="en" className='bg-slate-200'>
      <body className = {signika.className}>
        {children}
      </body>
    </html>
  )
}