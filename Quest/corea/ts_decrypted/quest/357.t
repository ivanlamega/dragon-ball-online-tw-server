CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 357;
	title = 35702;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 100;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 35709;
				ctype = 1;
				idx = 6312101;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 35708;
				gtype = 0;
				area = 35701;
				goal = 35704;
				grade = 132203;
				rwd = 100;
				sort = 35705;
				stype = 1;
				taid = 1;
				title = 35702;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 35714;
			nextlnk = 254;
			rwdtbl = 35701;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3172203;
			}
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "100;";
			type = 1;
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 35708;
			gtype = 0;
			oklnk = 2;
			area = 35701;
			goal = 35704;
			sort = 35705;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 35702;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 35707;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCRace
			{
				raceflg = 2;
			}
			CDboTSClickNPC
			{
				npcidx = 6312101;
			}
			CDboTSCheckLvl
			{
				maxlvl = 27;
				minlvl = 19;
			}
			CDboTSCheckClrQst
			{
				and = "356;";
			}
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
		}
	}
}

