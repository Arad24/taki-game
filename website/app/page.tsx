'use client'
import React, { useState, useEffect } from 'react';
import { useRouter } from "next/navigation";
import { useGlobalState } from './globals';
import Image from 'next/image'

// Pages
import Logged from './Logged'
import Card from './Card'

// Images
import imgJoinGame from './join_game.svg'
import imgStats from './statistics.svg'
import imgCreateGame from './create_game.svg'
import imgRanking from './ranking.svg'
import logo from './taki_logo.png';



const GameOptions = () => {
  return (
    <div className='pt-8 lg:mx-10'>
      <div className='flex flex-col lg:flex-row lg:mx-10'>
        <Card 
          title="Create taki game"
          content='You can join into online games and earn points & upgrades your statistics.' 
          image={imgCreateGame} 
          btnLink = '/create-room'
        />
        <Card 
          title="Join into game"
          content='You can join into online games and earn points & upgrades your statistics.' 
          image={imgJoinGame} 
          btnLink = '/rooms'
        />
      </div>

      <div className='flex flex-col lg:flex-row lg:mx-10'>
        <Card 
            title="See personal statistics"
            content='You can see your personal statistics in the game that you played.' 
            image={imgStats} 
            btnLink = '/personal-statistics'
          />
          <Card 
            title="See top 5 best players"
            content='You can see the top 5 list of players with the most points.' 
            image={imgRanking} 
            btnLink = '/top-5'
          />
      </div>
    </div>
    
  );
}

const HomeBarLink = () => {
  return (
    <div>
      <a href="./">
        <Image src={logo} alt="My Image" width={100} height={100} className='cursor-pointer'/>
      </a>
    </div>
  );
}

const NavBarLink = ({linkTo, LinkName} : {linkTo : string, LinkName: string}) => {
  return (
    <div>
      <a className=' text-white bg-green-500 mx-4 py-2 px-4 rounded-md shadow-[0_3px_0_rgb(90,90,90)] hover:shadow-[0_2px_0px_rgb(40,40,40)] transition-all duration-400 hover:bg-[rgb(24,154,71)] hover:mt-2' href={linkTo}>{LinkName}</a>
    </div>
  )
}

const MyNavBar = ({ username }: { username: string }) => {
  // Fix server & client unmatched sting
  const [clientRendered, setClientRendered] = useState(false);
  useEffect(() => {
    setClientRendered(true);
  }, []);

  return (
    <div className=' bg-white shadow-md border-blue-500 h-16'>
      <div className=' ml-12 flex items-center h-16 absolute'>
        <HomeBarLink />
      </div>
      <div className='mr-10 flex justify-end items-center h-16'>
      { clientRendered && username != '' && <Logged/> }
      { clientRendered && username == '' && 
        <React.Fragment>
          <NavBarLink linkTo='/login' LinkName='Login'/>
          <NavBarLink linkTo='/signup' LinkName='Sign up'/> 
        </React.Fragment>
      }
      
      </div>
    </div>
  )
}

export default function Home() {
  const [global_username] = useGlobalState("username");

  return (
    <main className=" bg-slate-200 w-full h-full">
      <div>
        <MyNavBar username={global_username} />
      </div>
      <div>
        <GameOptions />
      </div>
    </main>
  )
}