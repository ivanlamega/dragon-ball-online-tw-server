CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 453;
	title = 45302;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 4;
			elnk = 255;
			nextlnk = 3;
			prelnk = "2;";
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "3;2;";
		}
		CDboTSContUsrSel
		{
			cancellnk = 252;
			cid = 3;
			lilnk = 255;
			ndesc0 = 45333;
			uspt = -1;
			desc = 45332;
			nid2 = 100;
			type = 0;
			ust = 0;
			idx = 1654108;
			ndesc2 = 45335;
			nid1 = 99;
			prelnk = "4;";
			ndesc1 = 45334;
			nid0 = 98;
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 4;
			prelnk = "1;";

			CDboTSActRegQInfo
			{
				cont = 45308;
				gtype = 1;
				area = 45301;
				goal = 45304;
				grade = 132203;
				rwd = 100;
				sort = 45305;
				stype = 2;
				taid = 1;
				title = 45302;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 98;
			desc = 45336;
			nextlnk = 254;
			rwdtbl = 45303;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 1654108;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 99;
			desc = 45336;
			nextlnk = 254;
			rwdtbl = 45302;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 1654108;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 45307;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 1654108;
			}
			CDboTSCheckPCRace
			{
				raceflg = 4;
			}
			CDboTSCheckLvl
			{
				maxlvl = 18;
				minlvl = 10;
			}
			CDboTSCheckClrQst
			{
				and = "451;452;";
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 45308;
			gtype = 1;
			oklnk = 2;
			area = 45301;
			goal = 45304;
			sort = 45305;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 45302;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 45314;
			nextlnk = 254;
			rwdtbl = 45301;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 1654108;
			}
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "99;98;100;";
			type = 1;
		}
	}
}

