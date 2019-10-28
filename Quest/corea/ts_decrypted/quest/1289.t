CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1289;
	title = 128902;

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
				conv = 128909;
				ctype = 1;
				idx = 7611203;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 128908;
				gtype = 1;
				area = 128901;
				goal = 128904;
				grade = 132203;
				rwd = 100;
				sort = 128905;
				stype = 1;
				taid = 1;
				title = 128902;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 128907;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 7611203;
			}
			CDboTSCheckLvl
			{
				maxlvl = 52;
				minlvl = 44;
			}
			CDboTSCheckClrQst
			{
				and = "1288;";
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 128908;
			gtype = 1;
			oklnk = 2;
			area = 128901;
			goal = 128904;
			sort = 128905;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 128902;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 128914;
			nextlnk = 254;
			rwdtbl = 128901;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4372101;
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
	}
}

