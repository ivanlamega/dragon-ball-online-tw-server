CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 647;
	title = 64702;

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
				conv = 64709;
				ctype = 1;
				idx = 3032103;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 64708;
				gtype = 1;
				area = 64701;
				goal = 64704;
				grade = 132203;
				rwd = 100;
				sort = 64705;
				stype = 2;
				taid = 1;
				title = 64702;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 64707;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCRace
			{
				raceflg = 1;
			}
			CDboTSClickNPC
			{
				npcidx = 3032103;
			}
			CDboTSCheckLvl
			{
				maxlvl = 30;
				minlvl = 22;
			}
			CDboTSCheckClrQst
			{
				and = "646;";
			}
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
			cont = 64708;
			gtype = 1;
			oklnk = 2;
			area = 64701;
			goal = 64704;
			sort = 64705;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 64702;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 64714;
			nextlnk = 254;
			rwdtbl = 64701;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3221205;
			}
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

