CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 590;
	title = 59002;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGCond
		{
			cid = 3;
			prelnk = "2;";
			nolnk = 255;
			rm = 0;
			yeslnk = 100;

			CDboTSTeleport
			{
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 59007;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCRace
			{
				raceflg = 4;
			}
			CDboTSCheckLvl
			{
				maxlvl = 15;
				minlvl = 2;
			}
			CDboTSClickNPC
			{
				npcidx = 8512105;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 59014;
			nextlnk = 254;
			rwdtbl = 59001;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 8512105;
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
				conv = 59009;
				ctype = 1;
				idx = 8512105;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 59008;
				gtype = 0;
				area = 59001;
				goal = 59004;
				grade = 132203;
				rwd = 100;
				sort = 59005;
				stype = 1;
				taid = 1;
				title = 59002;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 59008;
			gtype = 0;
			oklnk = 2;
			area = 59001;
			goal = 59004;
			sort = 59005;
			prelnk = "0;";
			ds = 1;
			grade = 0;
			rwd = 100;
			title = 59002;
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "1;0;252;";
			type = 0;
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "100;";
			type = 1;
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
	}
}

