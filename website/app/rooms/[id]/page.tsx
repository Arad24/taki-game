'use client'
import Image from 'next/image'
import { useGlobalState, setGlobalState } from '../../globals';
import { useEffect, useState } from 'react';
import { sendMsg, getJsonResponse } from '../../websocket';
import { useRouter } from 'next/navigation';


const getStateCode = process.env.GETROOMSTATE_CODE;
const closeRoomCode = process.env.CLOSEROOM_CODE;
const leaveRoomCode = process.env.LEAVEROOM_CODE;
const startCode = process.env.STARTGAME_CODE;
const succesCode = process.env.SUCCESS;
const CLOSED  = '0';
const WAITING = '1';
const INGAME  = '2';
let isGameStart = false;

const Roomname = ({name} : {name : string}) => {
    return (
        <div className=' w-screen mt-3 items-center text-center'>
            <p className='text-black text-6xl font-light'>{name}</p>
        </div>
    );
}

const Waitingroom = ({players} : {players: string[]}) => 
{

  return (
    <div className=' grid grid-cols-2 gap-16 mt-24 mx-28 text-2xl md:grid-cols-4 lg:grid-cols-9 lg:mx-40'>
        {players.map((player, index) => (
            <p key={index} className='text-black font-semibold'>
                {player}
            </p>
        ))}
    </div>
  );
}

const Closebutton = ({router} : {router: any}) => 
{
    return (
        <div className=' flex justify-end items-center h-24'>
            <button onClick={closeRoom} className=" font-semibold border-red-500 text-red-500 border-2 px-3 py-1 rounded-sm hover:bg-red-500 transition-all duration-150 hover:text-white mt-8 ">Close room</button>
        </div>
    );
}

const LeaveButton = ({router} : {router: any}) => 
{
    return (
        <div className='flex justify-end items-center h-24'>
            <button onClick={leaveRoom} className=" font-semibold border-red-500 text-red-500 border-2 px-3 py-1 rounded-sm hover:bg-red-500 transition-all duration-150 hover:text-white mt-8 ">Leave room</button>
        </div>
    );
}

function leaveRoom()
{
    sendToServer(leaveRoomCode!.charAt(0), '').then((res) => 
    {
        alert('leave room');
    })
}

function closeRoom()
{
    sendToServer(closeRoomCode!.charAt(0), '').then((res) => 
    {
        alert('room closed');
    })
}

function startGame()
{

    sendToServer(startCode!.charAt(0), '').then((res) => 
    {
        if(res.status == succesCode)
        {
            isGameStart = true;
        }
        
    })
}

const Startbutton = () => 
{
    return (
        <div className=' flex justify-end mr-4 items-center h-24'>
            <button onClick={startGame} className=" font-semibold border-green-500 text-green-500 border-2 px-3 py-1 rounded-sm hover:bg-green-500 transition-all duration-150 hover:text-white mt-8 ">Start</button>
        </div>
    );
}

const HomeBarLink = ({id} : {id : string}) => {
  return (
    <div className='bg-blue-400 py-2 px-4 rounded-md flex justify-center gap-28 md:gap-44'>
        <div>
            <p className='text-xl text-center'>Room ID</p>
            <p className='text-6xl font-bold text-center'>{id}</p>
        </div>
      
    </div>
  );
}

const MyNavBar = ({ id} : {id : string}) => {
  return (
    <div className=' bg-white sticky shadow-md border-blue-500'>
      <div className=' flex justify-center items-center h-40'>
        <HomeBarLink id={id} />
      </div>
    </div>
  )
}

interface PostView
{
    params: {
        id: string;
    }
}


export default function Home(props: PostView) 
{
    const router = useRouter();
    const [players, setPlayers] = useState([]);
    const [isAdmin, setIsAdmin] = useGlobalState("isAdmin");


    useEffect(() => {
        const interval = setInterval(() => 
        {

            sendToServer(getStateCode!.charAt(0), '').then((res) => 
            {
                console.log(res)
                if(res.status == succesCode && res.hasGameBegun == WAITING)
                {
                    setPlayers(res.Players);
                }
                else
                {
                    if (isGameStart || res.hasGameBegun == INGAME)
                    {
                        isGameStart = true;
                        alert('Starting the game...');
                        
                        router.push(`${window.location.pathname}/ingame`);
                        clearInterval(interval);
                    }
                    else router.push('/');     
                }
            })
            .catch((error) => {
            console.error(error);
            });
            
        }, 1500);
    
        return () => {
            clearInterval(interval);
        };
    }, []);

    useEffect(() => 
    {
        if (isGameStart)
        {
            alert('Starting the game...');
            router.push(`${window.location.pathname}/ingame`);
        }

    }, [isGameStart])


  return (
    <main className=" bg-slate-200 w-screen h-screen">
      <div className=" w-screen h-16 fixed">
        <MyNavBar id={props.params.id}/>
      </div>
      <div className='pt-32 flex justify-end mr-7'>
        {isAdmin ? ( 
            <>
                <Startbutton />
                <Closebutton router={router}/> 
            </>
        ): 
            <LeaveButton router={router}/>
        }
        
      </div>
      <Waitingroom 
        players={players} 
      />
    </main>
  )
}


async function sendToServer(code: string, msg : string)
{
    try 
    {
        const response = await sendMsg(code, msg);
        const jsnRes = getJsonResponse(response);
        if (jsnRes.status == succesCode)
        {
            return jsnRes;
        } 
        else 
        {
            return '';
        }
    } 
    catch (error) {
        alert(error);
        return false;
    }
}