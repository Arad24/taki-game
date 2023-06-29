'use client'
import React, { useEffect, useState } from 'react';
import { sendMsg, getJsonResponse } from '../websocket';
import TakiLogo from '../taki_logo.png';
import Image from 'next/image';
import Room from './Room';

const getRoomsCode = process.env.GETROOMS_CODE;
const successCode = process.env.SUCCESS;

export default function Page() 
{
  const [rooms, setRooms] = useState([{}]);

  useEffect(() => 
  {
    const interval = setInterval(() => 
    {
      getRooms().then((result) => 
      {
        setRooms(result);
      })
      .catch((error) => 
      {
        console.error(error);
      });
    }, 3000);

    return () => {
      clearInterval(interval);
    };
    
  }, []);

  return (
    <main className=" bg-slate-200 w-screen h-screen">
      <div className=" w-screen h-16 fixed">
        <MyNavBar/>
      </div>
      <div className='pt-20 grid gap-10 mx-8 md:mx-28 lg:mx-16 lg:grid-cols-2 xl:grid-cols-3'>
      {rooms && rooms.map((room, index) => (
          <Room
            key={index}
            name={room.name}
            id={room.id}
            isActive={room.isActive}
            timePerPlay={room.timePerPlay}
            maxPlayers = {room.maxPlayers}
            currPlayers={room.currPlayers}
          />
        ))}
        
      </div>
    </main>
  )
}


async function getRooms() {
  try 
  {
    const response = await sendMsg(getRoomsCode!.charAt(0), '');
    const jsnRes = getJsonResponse(response);
    console.log(jsnRes);
    if (jsnRes.status == successCode) 
    {
      console.log(jsnRes);
      return jsnRes.Rooms;
    } 
    else 
    {
      alert(jsnRes.message);
      return [];
    }
  } 
  catch (error) 
  {
    alert(error);
    return [];
  }
}

const HomeBarLink = () => {
  return (
    <div>
      <a href="./">
        <Image src={TakiLogo} alt="My Image" width={100} height={100} className='cursor-pointer'/>
      </a>
    </div>
  );
}

const MyNavBar = () => {
  return (
    <div className=' bg-white sticky shadow-md border-blue-500'>
      <div className=' flex justify-center items-center h-16'>
        <HomeBarLink />
      </div>
    </div>
  )
}

