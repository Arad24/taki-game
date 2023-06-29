'use client'
import { sendMsg, getJsonResponse } from '../websocket';
import React, { useEffect, useState } from 'react';
import Image from 'next/image';
import cupImg from './cup.svg'


const getTop5Code = process.env.HIGHSCORE_CODE;
const succesCode = process.env.SUCCESS;

type Types = {
    name: string;
    place: number
};

const Ramp: React.FC<Types> = ({ name, place }) => 
{
    return (
        <div className='md:mx-52 mt-10'>
            <div className='bg-white h-32 px-20 rounded-md pt-5 shadow-md mb-5 lg:'>
                <div>
                    <h1 className='bg-amber-400 rounded-md px-5 text-center lg:text-2xl'>#{place + 1}</h1>
                    <p className='text-center mt-3 text-lg lg:text-2xl'>{name}</p>
                </div>
            </div>
            
        </div>
    )
}

async function getTop5() : Promise<Array<string>>
{
    try {
        const response = await sendMsg(parseInt(getTop5Code!.charAt(0)), '');
        const jsonRes = getJsonResponse(response);
        if (String.fromCharCode(jsonRes.status) == String.fromCharCode(succesCode)) 
        {
            return jsonRes.HighScores;
        } 
        else 
        {
          alert(response);
          return [];
        }
      } catch (error) {
        alert(error);
        return [];
      }
}

const Page = () =>
{
    const [players, setPlayers] = useState<string[]>([]);

    useEffect(() => {
        getTop5().then((topPlayers) => {
            setPlayers(topPlayers);
        })
        .catch((error) => {
            alert(error);
        });
    }, []);


    return(
        <div>
            <div className='bg-amber-400 mx-40 mt-10 rounded-lg lg:px-96 lg:mx-52 '>
                <Image src={cupImg} alt='img' className='h-10 mt-3'></Image>
                <h1 className='text-center text-xl'>statistics</h1>  
            </div>
            
            <div className="mt-20 flex-col justify-center">
                {players.map((player, index) => 
                (
                    <Ramp key={index} name={player} place={index} />
                ))} 
            </div>
        </div>
    )
}




export default Page;