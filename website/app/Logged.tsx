'use client';
import { useGlobalState, setGlobalState } from './globals';
import { useState, useEffect } from 'react';
import profileImg from './profile.svg';
import Image from 'next/image';
import { sendMsg, getJsonResponse } from './websocket';
import { useRouter } from 'next/navigation';

const logoutCode = process.env.LOGOUT_CODE;

const handleLogout = (global_username : string, router: any) =>
{
  
  handleMsg('').then((result) => { 
    if (result)
    {
      setGlobalState('username', '');
      localStorage.removeItem('username');
      router.push('/login')
    }
  });

  
}

export default function Logged() {
  const [global_username] = useGlobalState('username');
  const [isClick, setIsClick] = useState(false);
  const router = useRouter();

  return (
    <div className="flex">
      <h1 className="text-lg mr-3 mt-2">{global_username}</h1>
      <div>
        <Image src={profileImg} className="rounded-lg" onClick={(()=>{setIsClick(!isClick)})} alt="profileImg" width={40} height={40} />
        {isClick && (
          <div className="absolute mt-3 py-2 right-2 px-10 bg-white rounded-sm shadow-lg">
            <button onClick={() => handleLogout(global_username, router)}>Logout</button>
          </div>
        )}
      </div>
    </div>
  );
}


function handleMsg(msg : string) : Promise<boolean>
{
  
  return sendMsg(logoutCode!.charAt(0), msg)
  .then((response) => 
  {
    const resJson = getJsonResponse(response);
    if (resJson.status == '1') 
    {
      alert('Success to logout');
      return true;
    } 
    else 
    {
      return false;
    }
  })
  .catch((error) => {
    alert(error);
    return false;
  });
}