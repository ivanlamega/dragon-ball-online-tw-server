CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 596;
	title = 59602;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "100;";
			type = 1;
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "1;0;252;";
			type = 0;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 59614;
			nextlnk = 254;
			rwdtbl = 59601;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 6413106;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 59608;
			gtype = 2;
			oklnk = 2;
			area = 59601;
			goal = 59604;
			sort = 59605;
			prelnk = "0;";
			ds = 1;
			grade = 0;
			rwd = 100;
			title = 59602;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 59607;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckLvl
			{
				maxlvl = 20;
				minlvl = 10;
			}
			CDboTSClickNPC
			{
				npcidx = 6413106;
			}
			CDboTSCheckPCRace
			{
				raceflg = 4;
			}
			CDboTSCheckClrQst
			{
				and = "593;";
			}
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 59609;
				ctype = 1;
				idx = 6413106;
				taid = 2;
			}
			CDboTSActItem
			{
				iidx0 = 1041003;
				stype0 = 1;
				taid = 3;
				type = 0;
			}
			CDboTSActRegQInfo
			{
				cont = 59608;
				gtype = 2;
				area = 59601;
				goal = 59604;
				grade = 132203;
				rwd = 100;
				sort = 59605;
				stype = 1;
				taid = 1;
				title = 59602;
			}
		}
		CDboTSContGCond
		{
			cid = 3;
			prelnk = "2;";
			nolnk = 255;
			rm = 0;
			yeslnk = 100;

			CDboTSHoipoiMix
			{
			}
		}
	}
	CNtlTSGroup
	{
		gid = 254;

		CDboTSContGAct
		{
			cid = 1;
			elnk = 255;
			nextlnk = 254;
			prelnk = "0;";

			CDboTSActItem
			{
				iidx0 = 1041003;
				stype0 = 1;
				taid = 1;
				type = 1;
			}
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "1;";
			type = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 107;
			nolnk = 255;
			rm = 0;
			yeslnk = 1;
		}
	}
}

