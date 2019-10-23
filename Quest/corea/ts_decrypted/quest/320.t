CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 320;
	title = 32002;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContEnd
		{
			cid = 253;
			prelnk = "1;0;252;";
			type = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 32007;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 4152103;
			}
			CDboTSCheckPCRace
			{
				raceflg = 2;
			}
			CDboTSCheckLvl
			{
				maxlvl = 20;
				minlvl = 5;
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
				conv = 32009;
				ctype = 1;
				idx = 4152103;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 32008;
				gtype = 2;
				area = 32001;
				goal = 32004;
				grade = 132203;
				rwd = 100;
				sort = 32005;
				stype = 1;
				taid = 1;
				title = 32002;
			}
		}
		CDboTSContGCond
		{
			cid = 3;
			prelnk = "2;";
			nolnk = 255;
			rm = 0;
			yeslnk = 100;

			CDboTSUseMail
			{
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 32008;
			gtype = 2;
			oklnk = 2;
			area = 32001;
			goal = 32004;
			sort = 32005;
			prelnk = "0;";
			ds = 1;
			grade = 0;
			rwd = 100;
			title = 32002;
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 32014;
			nextlnk = 254;
			rwdtbl = 32001;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4152103;
			}
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "100;";
			type = 1;
		}
	}
}

