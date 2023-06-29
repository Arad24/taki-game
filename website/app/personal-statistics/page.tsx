'use client'
import { useEffect } from "react";
import React from 'react';
import Image from 'next/image';
import TakiLogo from '../taki_logo.png'
import { sendMsg, getJsonResponse } from '../websocket';
import { useGlobalState } from '../globals';

const getStatsCode = process.env.PERSONALSTATS_CODE;
const succesCode = process.env.SUCCESS;


const Stats = ({username, stats} : {username : string, stats: any}) => {
  return (
    <div className="pt-32">
      <h1 className="text-center text-white bg-blue-700 mx-14 py-5 rounded-md text-5xl lg:mx-52">
        {username}
      </h1>
      <div className="text-white font-semibold text-center ">
        <p className=' mt-10 bg-blue-500 mx-14 py-5 rounded-md lg:mx-52 lg:text-3xl'>
          Games: {stats[0]}
        </p>
        <p className='mt-10 bg-blue-500 mx-14 py-5 rounded-md  lg:mx-52 lg:text-3xl'>
          Wins: {stats[1]}
        </p>
        <p className='mt-10 bg-blue-500 mx-14 py-5 rounded-md  lg:mx-52 lg:text-3xl'>
          Average Cards Left: {stats[2]}
        </p>
        <p className='mt-10 bg-blue-500 mx-14 py-5 rounded-md lg:mx-52 lg:text-3xl'>
          Average Played Time: {stats[3]}
        </p>
        <p className='mt-10 bg-blue-500 mx-14 py-5 rounded-md  lg:mx-52 lg:text-3xl'>
          Score: {stats[4]}
        </p>
      </div>
    </div>
  )
}

const HomeBarLink = () => 
{
    return (
      <div>
        <a href="./">
          <Image src={TakiLogo} alt="My Image" width={100} height={100} className='cursor-pointer hover:p-1 transition-all duration-75'/>
        </a>
      </div>
    )
}
  
const MyNavBar = () => 
{
    return (
      <div className=' bg-white sticky shadow-md border-blue-500'>
        <div className=' mr-12 flex justify-center items-center h-16 w-screen'>
          <HomeBarLink />
        </div>
      </div>
    )
}
  
export default function Statistics() 
{
  const [statistics, setStats] = React.useState([]);
  const [global_username, setUsername] = useGlobalState("username");

  useEffect(() =>
  {
    getStatistics(global_username).then((result) => 
    {
        setStats(result);
      }).catch((error) => {
        console.error(error);
      });
  }, [])
  
    return (
      <main className=" bg-slate-200 w-screen h-screen">
        <div className=" w-screen h-16 fixed">
          <MyNavBar/>
        </div>
        <div>
          <Stats username={global_username} stats={statistics} />
        </div>
      </main>
    )
  
}

async function getStatistics(msg : string)
{
    try {
        const response = await sendMsg(getStatsCode!.charAt(0), msg);
        const jsnRes = getJsonResponse(response);

        if (String.fromCharCode(jsnRes.status) == String.fromCharCode(succesCode)) 
        {
          console.log(jsnRes.UserStatistics);
          return jsnRes.UserStatistics;
        } 
        else 
        {
          alert(response);
          return false;
        }
      } catch (error) {
        alert(error);
        return false;
      }
}