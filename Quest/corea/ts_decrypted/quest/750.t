CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 750;
	title = 75002;

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
				conv = 75009;
				ctype = 1;
				idx = 7131111;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 75008;
				gtype = 1;
				area = 75001;
				goal = 75004;
				grade = 132203;
				rwd = 100;
				sort = 75005;
				stype = 2;
				taid = 1;
				title = 75002;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 75014;
			nextlnk = 254;
			rwdtbl = 75001;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3031101;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 75007;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCRace
			{
				raceflg = 2;
			}
			CDboTSClickNPC
			{
				npcidx = 7131111;
			}
			CDboTSCheckLvl
			{
				maxlvl = 33;
				minlvl = 25;
			}
			CDboTSCheckClrQst
			{
				and = "749;";
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
			cont = 75008;
			gtype = 1;
			oklnk = 2;
			area = 75001;
			goal = 75004;
			sort = 75005;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 75002;
		}
	}
}

