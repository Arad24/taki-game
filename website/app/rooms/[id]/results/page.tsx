'use client'
import Image from 'next/image'
import { useGlobalState, setGlobalState } from '../../../globals';
import { useEffect, useState } from 'react';
import { sendMsg, getJsonResponse } from '../../../websocket';
import { useRouter } from 'next/navigation';
import TakiLogo from '../../../taki_logo.png'

const getResultsCode = process.env.GETGAMERESULTS_CODE;
const succesCode = process.env.SUCCESS;

const Card = ({username, numbercards, place} : {username : string, numbercards : number, place : number}) => {
  return (
    <div className=' bg-white w-8/12 rounded-lg border-black shadow-lg py-4 m-auto items-center text-center mb-8'>
      <div className=''>
        <p className=' text-black font-bold text-2xl'>Name</p>
        <p className=' text-black font-light text-2xl'>{username}</p>
      </div>
      <div className='mt-2'>
        <p className=' text-black font-bold text-2xl'>Cards</p>
        <p className=' text-black font-light text-2xl'>{numbercards}</p>
      </div>
      <div className='mt-2'>
        <p className=' text-black font-bold text-2xl '>Place</p>
        <p className=' text-black font-light text-2xl '>#{place}</p>
      </div>
    </div>
  );
}

/*


*/
const HomeBarLink = () => {
  return (
    <div>
      <a href="/">
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

export default function Home() 
{
    const [global_username, setGUsername] = useGlobalState('username');
    const [players, setPlayers] = useState([{}]);

    useEffect(() => 
    {
        sendToServer(getResultsCode!.charAt(0), '').then((res) => 
        {
          if (res != '') setPlayers(res.Results);
        })
        .catch((error) => 
        {
            console.error(error);
        });
    }, [])

  return (
    <main className=" bg-slate-200 w-screen h-screen">
      <div className=" w-screen h-16 fixed">
        <MyNavBar/>
      </div>
      <div className='pt-28'>
        {Array.isArray(players) && players.map((player, index) => (
          <Card username={player.username} numbercards={player.cardsInHand} place={player.place}/>
        ))}
        
      </div>
    </main>
  )
}


async function sendToServer(code: string, msg : string)
{
    try 
    {
        const response = await sendMsg(code, msg);
        const jsnRes = getJsonResponse(response);
        console.log(jsnRes);
        if (jsnRes.status == succesCode)
        {
            return jsnRes;
        } 
        else 
        {
            console.log(jsnRes.message)
            return '';
        }
    } 
    catch (error) 
    {
        console.error(error);
        return false;
    }
}